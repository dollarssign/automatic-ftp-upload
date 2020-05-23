#pragma once
#include <string>
#include <Windows.h>
#include <wininet.h>
#include <iostream>
#include <filesystem>
#pragma comment( lib, "Wininet" )

namespace utils {
	[[nodiscard]] inline std::string file_extension( const std::string& file ) {
		return file.substr( file.find_last_of( '.' ) + 1 );
	}

	[[nodiscard]] inline int file_size( const std::string& file_directory ) {
		if ( !std::filesystem::exists( file_directory ) ) {
			std::cout << "directory failed ( c_utils::file_size )" << std::endl;
			system( "pause" );
			ExitProcess( -1 );
		}

		return std::filesystem::file_size( file_directory );
	}

	inline void upload_ftp( const std::string& hostname, const std::string& username, const std::string& password, const std::string& file_directory, const std::string& ftp_directory ) {
		const auto internet_handle = InternetOpenA( nullptr, INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0 );
		if ( !internet_handle ) {
			system( "pause" );
			ExitProcess( -1 );
		}

		const auto internet_connect = InternetConnectA( internet_handle, hostname.c_str( ), INTERNET_DEFAULT_FTP_PORT, username.c_str( ), password.c_str( ), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0 );
		if ( !internet_connect ) {
			std::cout << "internet_connect failed ( c_utils::upload_ftp ) " << std::endl;
			system( "pause" );
			ExitProcess( -1 );
		}

		const auto upload_file = FtpPutFileA( internet_connect, file_directory.c_str( ), std::string( ftp_directory ).append( "automaticupload." ).append( file_extension( file_directory ) ).c_str( ), FTP_TRANSFER_TYPE_BINARY, 0 );
		if ( !upload_file ) {
			std::cout << "upload_file failed ( c_utils::upload_ftp ) " << std::endl;
			system( "pause" );
			ExitProcess( -1 );
		}

		std::cout << "file uploaded! " << std::endl;
	}
};

namespace globals {
	inline std::string file_directory, ftp_hostname, ftp_username, ftp_password, ftp_directory;
};