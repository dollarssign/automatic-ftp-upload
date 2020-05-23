#include <string>
#include <iostream>
#include "utils/config.hh"

int main( ) {
	if ( config::run_ask( ) ) {
		static std::string answer;
		
		std::cout << "config file found, want to make a new config? (y / n): " << std::endl;
		std::getline( std::cin, answer );

		if ( answer == "y" ) goto START; else goto UPLOAD_FTP_PART;
	}

START:
	
	std::cout << "Please enter the directory of the file you want to upload: ";
	if ( !std::getline( std::cin, globals::file_directory ) )
		return 0;

	std::cout << "please enter your ftp hostname: ";
	if ( !std::getline( std::cin, globals::ftp_hostname ) )
		return 0;

	std::cout << "please enter your ftp username: ";
	if ( !std::getline( std::cin, globals::ftp_username ) )
		return 0;

	std::cout << "please enter your ftp password: ";
	if ( !std::getline( std::cin, globals::ftp_password ) )
		return 0;

	std::cout << "please enter your ftp directory (where you want to put the automatic uploaded file in, leave blank if you want it to the default directory, example: folder/folder2/): ";
	if ( !std::getline( std::cin, globals::ftp_directory ) )
		return 0;

	config::save_config( globals::file_directory, globals::ftp_hostname, globals::ftp_username, globals::ftp_password, globals::ftp_directory );

UPLOAD_FTP_PART:
	config::load_config( );
	while ( true ) {
		static auto backup_file_size = 0;
		const auto file_size = utils::file_size( globals::file_directory );
		
		if ( backup_file_size != file_size ) {
			std::cout << std::endl << "file change detected (unless it's the first open)" << std::endl;

			utils::upload_ftp( globals::ftp_hostname, globals::ftp_username, globals::ftp_password, globals::file_directory, globals::ftp_directory );
				
			backup_file_size = file_size;
		}
	}
}
