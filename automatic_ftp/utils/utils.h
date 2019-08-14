#pragma once

class c_utils {
private:
	std::string check_file_extension( const std::string& file ) const {
		return file.substr( file.find_last_of( '.' ) + 1 );
	}
public:
	auto check_file_size( const std::string& file_directory ) const -> int {
		if ( !std::experimental::filesystem::exists( file_directory ) ) {
			std::cout << "directory failed ( c_utils::check_file_size )" << std::endl;
			return 0;
		}
		
		return std::experimental::filesystem::file_size( file_directory );
	}
	auto upload_ftp( const std::string& hostname, const std::string& username, const std::string& password, const std::string& file_directory ) const -> void {
		const auto internet_handle = InternetOpenA( nullptr, INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0 );
		if ( !internet_handle ) {
			std::cout << "internal_handle failed ( c_utils::upload_ftp ) " << std::endl;
			return;
		}
		
		const auto internet_connect = InternetConnect( internet_handle, hostname.c_str( ), INTERNET_DEFAULT_FTP_PORT, username.c_str( ), password.c_str( ), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0  );
		if ( !internet_connect ) {
			std::cout << "internet_connect failed ( c_utils::upload_ftp ) " << std::endl;
			return;
		}

		const auto upload_file = FtpPutFile( internet_connect, file_directory.c_str( ), std::string( "automaticupload." ).append( check_file_extension( file_directory ) ).c_str( ), FTP_TRANSFER_TYPE_BINARY, 0 );
		if ( !upload_file ) {
			std::cout << "upload_file failed ( c_utils::upload_ftp ) " << std::endl;
			return;
		}

		std::cout << "file uploaded! " << std::endl;
		return;
	}
};

struct c_global {
public:
	std::string file_directory, ftp_hostname, ftp_username, ftp_password;
};

extern c_global global;
extern c_utils utils;
