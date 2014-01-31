
#include <boost/filesystem.hpp>
#include "MainWindow.h"
#include "style.h"

#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QMessageBox>

#include <iostream>
#include <sstream>
#include <iomanip>

namespace fs=boost::filesystem;

MainWindow::MainWindow(){

  sample.reset(new sf::SoundBuffer());
  sound.reset(new sf::Sound());
  path=fs::current_path().string()+"/";
  seconds=-1;
  contents=new QWidget(this);
  contents->setStyleSheet(QString(Style::getStyleString().c_str()));
  setContents();

  
}

void MainWindow::setContents(){
  
  setWindowTitle("Music Player");
  setGeometry(200, 100, 300, 500);
  
  QVBoxLayout *songLayout = new QVBoxLayout();
  songList = new QListWidget(contents);
  loadFolder(path);
  songLayout->addWidget(songList);
  connect(songList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemSelected(QListWidgetItem*)));
  
  
  /* buttonLayout */
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  
  QPushButton *playButton = new QPushButton("play",contents);
  //playButton->setStyleSheet(Style::playButtonStyle().c_str());
  //playButton->setIcon(QIcon("../src/resources/button_black_play.png"));
  //playButton->setMinimumSize(70,50);
  //playButton->setIconSize(QSize(40,40));
  QPushButton *pauseButton = new QPushButton("pause",contents);
  QPushButton *stopButton = new QPushButton("stop",contents);
  
  connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause_song()));
  connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
  
  buttonLayout->addWidget(playButton);
  buttonLayout->addWidget(pauseButton);
  buttonLayout->addWidget(stopButton);

  slider=new QSlider(Qt::Horizontal,contents);
  slider->setValue(0.5*slider->maximum());
  sound->setVolume(50);
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));

  clock=new QLCDNumber(contents);
  clock->setSegmentStyle(QLCDNumber::Filled);
  timer=new QTimer(contents);
  connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
  showTime();
  
  QHBoxLayout *slidercllayout = new QHBoxLayout;
  slidercllayout->addWidget(slider);
  slidercllayout->addWidget(clock);


  /* mainLayout */
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(slidercllayout);
  mainLayout->addLayout(songLayout);
  mainLayout->addLayout(buttonLayout);
  
  
  contents->setLayout(mainLayout);
  setCentralWidget(contents);
}


bool MainWindow::loadFolder(const std::string path){

  fs::path songPath(path.c_str());

  if(fs::exists(songPath) && fs::is_directory(songPath)){

     songList->clear();
     songList->addItem("..");
    for(fs::directory_iterator iter =fs::directory_iterator(songPath); iter!=fs::directory_iterator(); ++iter){
      if(fs::is_directory(*iter))
	songList->addItem(iter->path().filename().c_str());
    }
    for(fs::directory_iterator iter =fs::directory_iterator(songPath); iter!=fs::directory_iterator(); ++iter){
      if(!fs::is_directory(*iter)){
	if(checkIsMusicFile(iter->path().filename().string()))
	  songList->addItem(iter->path().filename().c_str());
      }
    }
    songList->setCurrentRow(0);
    return true;
  }else
    return false;
}


void MainWindow::itemSelected(QListWidgetItem *item){
  
  if(!item->text().toStdString().compare("..")){
    if(path.find("/")!=path.rfind("/")){
      std::string temp_path=path.substr(0,path.length()-2);
      unsigned key=temp_path.rfind("/");
      path=path.substr(0,key+1);
      loadFolder(path);
    }
    return;
  }
  
  std::string temp_path=path+item->text().toStdString();
  if(loadFolder(temp_path))
    path=temp_path+"/";
  else
    playSong(temp_path);
}

void MainWindow::setVolume(int value){

  sound->setVolume((double)value/(slider->maximum())*100.0);
  
}

void MainWindow::playSong(std::string song){

  timer->stop();
  sound->stop();
  seconds=-1;
  showTime();
  sample.reset(new sf::SoundBuffer());
  sound.reset(new sf::Sound());
  if(!sample->loadFromFile(song))
    std::cout<<"something wrong\n";
  sound->setBuffer(*sample);
  sound->play();
  timer->start(1000);
}

bool MainWindow::checkIsMusicFile(std::string file){

  std::string fe=file.substr(file.length()-3,file.length()-1);

  if(!fe.compare("wav") || !fe.compare("ogg") || !fe.compare("mp3"))
    return true;

  return false;
}
  

void MainWindow::play(){

  sound->play();
}

void MainWindow::stop(){

  sound->stop();
  timer->stop();
  seconds=-1;
  showTime();


}

void MainWindow::pause_song(){
  
  sound->pause();
}

void MainWindow::showTime(){

	seconds++;
	int min=seconds/60;
	int sec=seconds%60;
	std::string sec_text;
	std::string min_text;
	std::stringstream text;

	text << std::setw(3) << std::setfill('0') <<min<<":";
    min_text=text.str();
    text.str("");
    text << std::setw(2)<<std::setfill('0')<<sec;
    sec_text=text.str();
    text.str("");
    text<<min_text<<sec_text;

	clock->display(QString(text.str().c_str()));
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindow window;
  window.show();

  return app.exec();
}
