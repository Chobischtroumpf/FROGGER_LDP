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

int main(int argc, char *argv[]) {
  MainWindow window(650, 650, "Frogger Game", 60);
  window.show(argc, argv);
  return Fl::run();
}
