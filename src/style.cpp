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
