void displayCurrentState(const std::string& guess, const std::string& secretWord) {
    // Display the ASCII art with color for specific letters
    std::cout << " --- --- --- --- --- ---\n";
    std::cout << "| " << (guess[0] == secretWord[0] ? GREEN : guess[0] == secretWord[1] ? YELLOW : GRAY) << guess[0] << RESET_COLOR << " | | ";
    std::cout << (guess[1] == secretWord[1] ? GREEN : guess[1] == secretWord[0] ? YELLOW : GRAY) << guess[1] << RESET_COLOR << " || ";
    std::cout << (guess[2] == secretWord[2] ? GREEN : guess[2] == secretWord[2] ? YELLOW : GRAY) << guess[2] << RESET_COLOR << " || ";
    std::cout << (guess[3] == secretWord[3] ? GREEN : guess[3] == secretWord[3] ? YELLOW : GRAY) << guess[3] << RESET_COLOR << " || ";
    std::cout << (guess[4] == secretWord[4] ? GREEN : guess[4] == secretWord[4] ? YELLOW : GRAY) << guess[4] << RESET_COLOR << " |\n";
    std::cout << " --- --- --- --- --- ---\n";
}
