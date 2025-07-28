/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------

File, String encryption and decryption using OpenSSL library.
 
***************************************************************************/

#ifndef ENCRYPT_DECRYPT_DATA_H_
#define ENCRYPT_DECRYPT_DATA_H_

class EncryptDecryptData
{
public:
	EncryptDecryptData();
	~EncryptDecryptData();
	bool EncryptFile(const std::string &input_file, const std::string &output_file);
	bool DecryptFile(const std::string &input_file, const std::string &output_file);
	std::string EncryptString(const std::string &plaintext);
	std::string DecryptString(const std::string &ciphertext);
	std::string ConvertHexToEncryptedData(const std::string& hex);
	std::string ConvertEncryptedDataToHexString(const std::string& data);
	static std::string GetEncryptionDecryptionPassword();
	static std::string GetDataStreamingEncryptionPassword();
	int EncryptTCPIPStreamData(unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext);
private:	
	size_t m_LogID;
	static std::string decode(const std::string enc);
};

#endif // ENCRYPT_DECRYPT_DATA_H_
