#pragma once
#include <fstream>
#include <shlobj.h>
#include <filesystem>
#include <iomanip>
#include "json.hh"
#include "utils.hh"

inline nlohmann::json json;

namespace config {
	inline std::string get_config_directory( ) {
		char my_documents[MAX_PATH];
		SHGetFolderPathA( nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents );

		return std::string( my_documents ).append( "\\" ).append( "automatic_ftp.cfg" );
	}

	inline auto save_config( const std::string& file_directory, const std::string& ftp_hostname, const std::string& ftp_username, const std::string& ftp_password, const std::string& ftp_directory ) -> void {
		auto output_file = std::ofstream( get_config_directory( ) );
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

	inline void load_config( ) {
		auto input_file = std::ifstream( get_config_directory( ) );
		if ( !input_file.good( ) )
			return;

		json << input_file;

		globals::file_directory = json["file_directory"].get<std::string>( );
		globals::ftp_hostname = json["hostname"].get<std::string>( );
		globals::ftp_username = json["username"].get<std::string>( );
		globals::ftp_password = json["password"].get<std::string>( );
		globals::ftp_directory = json["ftp_directory"].get<std::string>( );

		input_file.close( );

	}

	inline bool run_ask( ) {
		return std::filesystem::exists( get_config_directory( ) );
	}
};
