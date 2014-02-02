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


#include "style.h"
#include <string>


std::string Style::getStyleString(){
	std::string style_string="QWidget {background-color:black} \
    QListWidget,QPushButton {color:red; background:black}";
	return style_string;
}

std::string Style::playButtonStyle(){

	std::string play_button_string="background-image: \
			url(../src/resources/button_black_play.png); \
			background-attachment: fixed";

	return play_button_string;

}
