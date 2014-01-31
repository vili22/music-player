#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <boost/shared_ptr.hpp>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QListWidget>
#include <QLCDNumber>
#include <QTimer>
#include <SFML/Audio.hpp>
#include <string>
   
class MainWindow : public QMainWindow{
  
  Q_OBJECT
    public:
  
  /** Constructor
   * Setup a new launcher window and search for songs in ../resources/songs directory
   */
  MainWindow();
  
  private slots:

  void stop();
  void pause_song();
  void play();
  void itemSelected(QListWidgetItem *item);
  void setVolume(int value);
  void showTime();
   
 private:

  bool loadFolder(std::string path);
  void playSong(std::string song);
  bool checkIsMusicFile(std::string file);
  void setContents();
  std::string path;
  QListWidget *songList;
  QSlider *slider;
  QWidget *contents;
  QLCDNumber *clock;
  QTimer *timer;
  int seconds;
  boost::shared_ptr<sf::SoundBuffer> sample; 
  boost::shared_ptr<sf::Sound> sound; 
};


#endif

