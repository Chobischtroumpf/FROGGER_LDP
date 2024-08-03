/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alessandro Dorigo                          +#+  +:+       +#+        */
/*   And : Gabriel Goldsztajn                     +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:48 by adorigo           #+#    #+#             */
/*   Updated: 2023/11/13 16:04:49 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "GameModel.hpp"
#include "GameView.hpp"
#include "GameController.hpp"
#include "DisplaySettings.hpp"
#include <iostream>

void gameLoopCallback(void* controller_ptr) {
    GameController* controller = static_cast<GameController*>(controller_ptr);
    
    controller->gameLoop();

    // Repeat the gameloop every 1 / 60th of a second
    Fl::repeat_timeout(1.0 / 60, gameLoopCallback, controller_ptr);
}

int main(int argc, char** argv) {

  
  /*
  * From line 23 to line 34, as well as line 42 and 43 is copy pasted code that was written by myself
  * for the project in the Projet d'Informatique 2 course, and can be found at the following repository:
  * https://github.com/Chobischtroumpf/Bataille-Navale-Projet-Informatique-2/blob/master/src/Client/main.cc
  */ 
  #ifdef OUTPUT_DEBUG // If the macro OUTPUT_DEBUG is defined at compile time, the program will output debug information to a log file
    std::cout << "Debug mode enabled" << std::endl;
    std::ofstream ofs("/tmp/froggers.log",
                      std::ofstream::out |
                          std::ofstream::app); // Create a log file and open it as
                                              // output stream in append mode
  #else // otherwise, the program will output debug information to /dev/null, a special file that discards all data written to it
    std::cout << "Debug mode disabled" << std::endl;
    std::ofstream ofs("/dev/null",
                      std::ofstream::out |
                          std::ofstream::app); // sends log to /dev/null
  #endif

    auto clog_buf = std::clog.rdbuf(); // Save the original std::clog buffer
    std::clog.rdbuf(ofs.rdbuf());      // Redirect std::clog to the log file


    // Initialize mvc instances
    
    std::cout << "Initializing model" << std::endl;
    GameModel model;
    std::cout << "Initializing Controller" << std::endl;
    
    GameView* view = nullptr;
    GameController controller(&model, view);

    std::cout << "Initializing View" << std::endl;
    view = new GameView(DisplaySettings::windowSize, DisplaySettings::windowSize, &model, &controller);

    controller.linkView(view); // Set the view in the controller

    std::cout << "Displaying view" << std::endl;
    // Display the view
    view->show(argc, argv);
    
    std::cout << "Starting game loop" << std::endl;
    // Game loop using FLTK timeout
    Fl::add_timeout(1.0 / 60, gameLoopCallback, &controller);

    
    
    
    int retval = Fl::run();
    std::clog.rdbuf(clog_buf); // Restore the original std::clog buffer
    ofs.close(); // Close the log file

    return retval;
}

