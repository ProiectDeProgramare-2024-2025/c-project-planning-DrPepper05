#include "commands/view_offers_command.h"
#include "offer_manager.h"
#include "ansi.h" // Added for colors
#include <iostream>
#include <iomanip> // For std::setw
#include <string>  // For std::to_string

ViewOffersCommand::ViewOffersCommand() : Command({"view_offers"}) {}

int ViewOffersCommand::execute(std::vector<std::string> args) {
  OfferManager offer_manager;
  const auto &offers = offer_manager.getEntries();

  if (offers.empty()) {
    std::cout << COLOR("No offers available at the moment.", YEL) << std::endl;
    return 0;
  }

  std::cout << COLOR("Available Offers:", BCYN) << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;
  std::cout << COLOR("Name                | Price (RON) | Duration (min) ", BYEL) << std::endl;
  std::cout << "----------------------------------------------------------" << std::endl;

  for (const auto &offer : offers) {
    std::cout << std::left << std::setw(20) << WHT << offer.name << CRESET
              << "| " << std::right << std::setw(11) << WHT << std::to_string(offer.price) << CRESET
              << " | " << std::setw(14) << WHT << std::to_string(offer.duration.count()) << CRESET
              << std::endl;
  }
  std::cout << "----------------------------------------------------------" << std::endl;

  return 0;
}
