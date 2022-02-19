/*
 * Copyright 2022 Ralph Lynch
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	// Checks if the user has passed a file as an argument
	if (argc < 2) {
		std::cerr << "Error: no file specified" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Opens the file containing the program
	std::ifstream program_file(argv[1]);

	// Ends the program if the file cannot be opened
	if (program_file.fail()) {
		std::cerr << "Error: unable to open file" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Creates the mailboxes and fills them with 000
	std::array<std::string, 100> mailboxes;
	mailboxes.fill("000");

	// Copies the contents of program_file to mailboxes
	for (auto i = mailboxes.begin(); i != mailboxes.end() && !program_file.eof();
		++i) {
		program_file >> *i;
	}

	program_file.close();

	int program_counter{ 0 }, accumulator{ 0 }, instruction_register{ 0 },
		address_register{ 0 };

	// Fetch-execute cycle
	while (program_counter < mailboxes.size()) {
		// Stores the opcode and operand in registers
		instruction_register = std::stoi(mailboxes[program_counter].substr(0, 1));
		address_register = std::stoi(mailboxes[program_counter].substr(1, 2));

		++program_counter;

		switch (instruction_register) {
		case 0:
			// HLT
			if (address_register == 0)
				program_counter = mailboxes.size();
			else {
				std::cerr << "Error: illegal operand at address "
					<< --program_counter << std::endl;
				std::exit(EXIT_FAILURE);
			}
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			// STA
			mailboxes[address_register] = std::to_string(address_register);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		}
	}
}
