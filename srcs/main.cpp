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
#include "MainWindow.hpp"

int main(int argc, char *argv[]) {

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

  MainWindow window;
  window.show();
  int retval = Fl::run();

  std::clog.rdbuf(clog_buf); // Restore the original std::clog buffer
  ofs.close(); // Close the log file

  return retval;
}
