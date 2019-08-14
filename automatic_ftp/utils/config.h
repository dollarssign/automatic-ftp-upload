#pragma once
#include "json.h"
#include <iomanip>
#include <fstream>
#include <shlobj.h>

nlohmann::json json;
class c_config {
public:
	auto get_config_directory( ) -> std::string {
		CHAR my_documents[MAX_PATH];
		SHGetFolderPath( nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents );

		return std::string( my_documents ).append( "\\" ).append( "automatic_ftp.cfg" );
	}
	auto save_config( const std::string& file_directory, const std::string& ftp_hostname, const std::string& ftp_username, const std::string& ftp_password, const std::string& ftp_directory ) -> void {
		std::ofstream output_file = std::ofstream( get_config_directory( ) );
		if ( !output_file.good( ) )
			return;

		json["file_directory"] = file_directory;
		json["hostname"] = ftp_hostname;
		json["username"] = ftp_username;
		json["password"] = ftp_password;
		json["ftp_directory"] = ftp_directory;

		output_file << std::setw( 4 ) << json << std::endl;
		output_file.close( );
	}
	auto load_config( ) -> void {
		auto input_file  = std::ifstream( get_config_directory( ) );
		if( !input_file.good( ) )
			return;

		json << input_file;
		
		global.file_directory = json["file_directory"].get<std::string>( );
		global.ftp_hostname = json["hostname"].get<std::string>( );
		global.ftp_username = json["username"].get<std::string>( );
		global.ftp_password = json["password"].get<std::string>( );
		global.ftp_directory = json["ftp_directory"].get<std::string>( );

		input_file.close( );

	}
	auto run_ask( ) -> bool {
		return std::experimental::filesystem::exists( get_config_directory( ) );
	}
};

extern c_config config;