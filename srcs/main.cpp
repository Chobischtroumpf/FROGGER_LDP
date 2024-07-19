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

#include "MainWindow.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "GameModel.hpp"
#include "GameView.hpp"
#include "GameController.hpp"
#include <iostream>

void gameLoopCallback(void* controller_ptr) {
    GameController* controller = static_cast<GameController*>(controller_ptr);
    
    controller->gameLoop();

    // Repeat the gameloop every 1 / 60th of a second
    Fl::repeat_timeout(1.0 / 60, gameLoopCallback, controller_ptr);
}

int main(int argc, char** argv) {
    // initialise mvc instances
    
    std::cout << "Initialising model" << std::endl;

    GameModel model;
    std::cout << "Initialising Controller" << std::endl;
    
    GameView* view = nullptr;
    GameController controller(&model, view);

    std::cout << "Initialising View" << std::endl;
    view = new GameView(1000, 1000, &model, &controller);

    controller.linkView(view); // Set the view in the controller

    std::cout << "Displaying view" << std::endl;
    // Display the view
    view->show(argc, argv);
    std::cout << "Starting game loop" << std::endl;
    // Game loop using FLTK timeout
    Fl::add_timeout(1.0 / 60, gameLoopCallback, &controller);

    return Fl::run();
}

