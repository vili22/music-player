/****************************************************************************
* This file is part of music-player
* Copyright (C) 2014 Ville Virkkala
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/


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

