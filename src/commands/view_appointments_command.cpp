#include "commands/view_appointments_command.h"
#include "appointment_manager.h"
#include "ansi.h" // Added for colors
#include <iostream>
#include <iomanip> // For std::setw and std::setfill
#include <string>  // For std::string

ViewAppointmentsCommand::ViewAppointmentsCommand()
    : Command({"view_appointments"}) {}

int ViewAppointmentsCommand::execute(std::vector<std::string> args) {
  AppointmentManager appointment_manager;
  const auto &appointments = appointment_manager.getEntries();

  if (appointments.empty()) {
    std::cout << COLOR("No appointments found.", YEL) << std::endl;
    return 0;
  }

  std::cout << COLOR("Appointments:", BCYN) << std::endl;
  std::cout << "--------------------------------------------------------------------------" << std::endl;
  std::cout << COLOR("Client Name       | Offer Name        | Date       | Time ", BYEL) << std::endl;
  std::cout << "--------------------------------------------------------------------------" << std::endl;

  for (const auto &appointment : appointments) {
    std::chrono::hh_mm_ss<std::chrono::minutes> time_display(appointment.time);
    
    std::ostringstream date_stream;
    date_stream << std::setfill('0') << std::setw(2) << (unsigned)appointment.date.day() << "/"
                << std::setfill('0') << std::setw(2) << (unsigned)appointment.date.month() << "/"
                << static_cast<int>(appointment.date.year()); // Ensure year is int for ostream
    std::string formatted_date = date_stream.str();

    std::ostringstream time_stream_display;
    time_stream_display << std::setfill('0') << std::setw(2) << time_display.hours().count() << ":"
                << std::setfill('0') << std::setw(2) << time_display.minutes().count();
    std::string formatted_time_display = time_stream_display.str();

    std::cout << std::left << std::setw(18) << WHT << appointment.client_name << CRESET
              << "| " << std::setw(18) << WHT << appointment.offer_name << CRESET
              << "| " << std::setw(11) << WHT << formatted_date << CRESET
              << "| " << WHT << formatted_time_display << CRESET
              << std::endl;
  }
  std::cout << "--------------------------------------------------------------------------" << std::endl;

  return 0;
}
