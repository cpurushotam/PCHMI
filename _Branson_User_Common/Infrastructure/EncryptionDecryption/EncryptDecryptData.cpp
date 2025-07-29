/************************************************************************** 

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
     
---------------------------- MODULE DESCRIPTION ----------------------------

File, String encryption and decryption using OpenSSL library.
 
***************************************************************************/
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "EncryptDecryptData.h"
#include "DataLogger.h"

//Password used for encryption and decryption

//Buffer size to use for file read during encrypt and decrypt operation
constexpr size_t READ_BUFFER_SIZE = 4096;
//Key size for AES 256 standard
constexpr int KEY_SIZE = 32;

// Original Password is BransonTopSecret@1234#, scattered in smaller parts, Added 1 in every character of defined strings
const std::string key_part1 = "Csbotpo";       // "Csbotpo" represent to "Branson" String
const std::string key_part2 = "Upq";           // "Upq" represent "Top" String
const std::string key_part3 = "Tfdsfu";        // "Tfdsfu" represent to "Secret" String
const std::string key_part4 = "A";             // "A" represent to "@" String
const std::string key_part5 = "2345$";         // "2345$" represent to "1234#" String

// Original Password is SecureStream#2025!, scattered in smaller parts, Added 1 in every character of defined strings
const std::string tcpip_key_part1 = "Tfdvsf";       // "Tfdvsf" represent to "Secure" String
const std::string tcpip_key_part2 = "Tusfbn";       // "Tusfbn" represent to "Stream" String
const std::string tcpip_key_part3 = "$";        	// "$" represent to "#" String
const std::string tcpip_key_part4 = "3136";         // "3136" represent to "2025" String
const std::string tcpip_key_part5 = std::string(1, '"');;         	// '"' represent to "!" String

/**************************************************************************//**
* \brief   - Decoded String. it will take scattered part of password as input, 
* 			 Subtract 1 from Every characters ASCII values, generate string and return
*
* \param   - Input string that decoded by subtracting 1 
* 		   - from its ASCII
*			
* \return  - Return one decoded part of Password String
*
******************************************************************************/
std::string EncryptDecryptData::decode(const std::string enc)
{
   std::string decoded;
   int i=0;
   while (enc[i])
   {
       decoded += (enc[i]-1);     // Subtracting 1 here, from Each character ASCII values of scattered Key string
       i++;
   }
   return decoded;
}

/**************************************************************************//**
* \brief   - Return the password used for encryption and decryption, By concatenation of Key_Parts defined.
*
* \param   - None 
*			
* \return  - Return the Password String
*
******************************************************************************/
std::string EncryptDecryptData::GetEncryptionDecryptionPassword() 
{
	return (decode(key_part1) + decode(key_part2) + decode(key_part3) + decode(key_part4) + decode(key_part5));
}

/**************************************************************************//**
* \brief   - Return the password used for TCP/IP DataStreaming encryption , By concatenation of tcpip_key_parts defined.
*
* \param   - None 
*			
* \return  - Return the Password String
*
******************************************************************************/
std::string EncryptDecryptData::GetDataStreamingEncryptionPassword() 
{
	return (decode(tcpip_key_part1) + decode(tcpip_key_part2) + decode(tcpip_key_part3) + decode(tcpip_key_part4) + decode(tcpip_key_part5));
}
/**************************************************************************//**
* \brief   - constructor
*
* \param   - none	
* \return  - none
*
******************************************************************************/
EncryptDecryptData::EncryptDecryptData()
{
	m_LogID = Logger::enroll(this);
}

/**************************************************************************//**
* \brief   - destructor
*
* \param   - none	
* \return  - none
*
******************************************************************************/
EncryptDecryptData::~EncryptDecryptData()
{

}

/**************************************************************************//**
* \brief   - Encrypt the file.
*
* \param   - input_file: Path of input file to be encrypted, 
*		   - output_file: Path of encrypted output file, 	
* \return  - true if file is successfully encrypted, else false
*
******************************************************************************/
bool EncryptDecryptData::EncryptFile(const std::string &input_file, const std::string &output_file)
{
    bool bResult = false;
    bool bErrorOccured = false;
    unsigned char key[KEY_SIZE] = {0}, iv[EVP_MAX_IV_LENGTH]  = {0};

    //Set the AES encryption algorithm
    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    char  msg[buff_size_config] = {0};
    			
    //Derive a key and IV from input parameters
    std::string EncryptionDecryptionPassword = GetEncryptionDecryptionPassword();
    if (EVP_BytesToKey(cipher, EVP_sha256(), nullptr, (const unsigned char*)EncryptionDecryptionPassword.c_str(), EncryptionDecryptionPassword.length(), 1, key, iv) != KEY_SIZE) 
    {
		snprintf(msg,buff_size_config,"EncryptFile_Failure_1");
	    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		bErrorOccured = true;
    }
    else
    {
	    //Allocate and return a cipher context.
	    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	    if (ctx == nullptr)
	    {
			snprintf(msg,buff_size_config,"EncryptFile_Failure_2");
		    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
			bErrorOccured = true;
	    }
		else
		{	//initialize cipher contex ctx.   
			if (EVP_CIPHER_CTX_init(ctx) == 0)
			{
				snprintf(msg,buff_size_config,"EncryptFile_Failure_3");
			    Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				bErrorOccured = true;
			}
			else
			{
				// Open input file for reading.
				BIO* inputFilePtr = BIO_new_file(input_file.c_str(), "rb");
				if (inputFilePtr == nullptr)
				{
					snprintf(msg,buff_size_config,"EncryptFile_Failure_4");
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					bErrorOccured = true;
				}
				else
				{
					// Open output file for writing.
					BIO* outputFilePtr = BIO_new_file(output_file.c_str(), "wb");
					if (outputFilePtr == nullptr)
					{
						snprintf(msg,buff_size_config,"EncryptFile_Failure_5");
						Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
						bErrorOccured = true;
					}
					else
					{
						// Initialize encryption BIO.
						BIO* encrypt = BIO_new(BIO_f_cipher());
						if (encrypt == nullptr)
						{
							snprintf(msg,buff_size_config,"EncryptFile_Failure_6");
							Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
							bErrorOccured = true;
						}
						else
						{
							//set the cipher of BIO "encrypt" to "cipher" using key "key" and IV "iv"
							if (BIO_set_cipher(encrypt, cipher, key, iv, 1) != 1)
							{
								snprintf(msg,buff_size_config,"EncryptFile_Failure_7");
								Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
								bErrorOccured = true;
							}
							else
							{
								BIO_push(encrypt, outputFilePtr);

								//Read the input file and create and encrypted output file.
								char buffer[READ_BUFFER_SIZE];
								int length = 0;
								while ( (length = BIO_read( inputFilePtr, buffer, sizeof(buffer) ) ) > 0)
								{
									if (BIO_write(encrypt, buffer, length) <= 0)
									{
										snprintf(msg,buff_size_config,"EncryptFile_Failure_8");
										Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
										bErrorOccured = true;
										break;
									}
								}
								//signal EOF and that no more data will be written.
								BIO_flush(encrypt);
							}
						}
						//free up an entire BIO chain
						BIO_free_all(outputFilePtr);
					}
					//free up an entire BIO chain
					BIO_free_all(inputFilePtr);
				}
				//clears all information from a cipher context
				EVP_CIPHER_CTX_cleanup(ctx);
			}
			//Clear all information from a cipher context and free any allocated memory associated with it
			EVP_CIPHER_CTX_free(ctx);
		}
    }

	if(bErrorOccured == false)
	{
		bResult = true;
	}
	return bResult;
}

/**************************************************************************//**
* \brief   - Decrypt the file.
*
* \param   - input_file: Path of input file to be decrypted, 
*		   - output_file: Path of decrypted output file, 	
* \return  - true if file is successfully decrypted, else false
*
******************************************************************************/
bool EncryptDecryptData::DecryptFile(const std::string &input_file, const std::string &output_file) 
{
	bool bResult = false;
	bool bErrorOccured = false;
	unsigned char key[KEY_SIZE] = {0};
	unsigned char iv[EVP_MAX_IV_LENGTH] = {0};
	char  msg[buff_size_config] = {0};
	EVP_CIPHER_CTX* ctx = nullptr;

	//Open encrypted input file
	std::ifstream in_file(input_file, std::ios::binary);
	if (!in_file) 
	{
		snprintf(msg,buff_size_config,"DecryptFile_Failure_1");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		bErrorOccured = true;
	}
	else
	{
		//Create decrypted output file
		std::ofstream out_file(output_file, std::ios::binary);
		if (!out_file) 
		{
			snprintf(msg,buff_size_config,"DecryptFile_Failure_2");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
			bErrorOccured = true;
		}
		else
		{
			//Allocate and return a cipher context.
			ctx = EVP_CIPHER_CTX_new();
			if (ctx == nullptr) 
			{
				snprintf(msg,buff_size_config,"DecryptFile_Failure_3");
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				bErrorOccured = true;
			}
			else
			{
				//Set the AES decryption algorithm
				const EVP_CIPHER* cipher = EVP_aes_256_cbc();
				if (cipher == nullptr) 
				{
					snprintf(msg,buff_size_config,"DecryptFile_Failure_4");
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					bErrorOccured = true;
				}
				else
				{
					//function for decryption operations
					if (EVP_DecryptInit_ex(ctx, cipher, nullptr, nullptr, nullptr) != 1) 
					{
						snprintf(msg,buff_size_config,"DecryptFile_Failure_5");
						Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
						bErrorOccured = true;
					}
					else
					{	
						//Derive a key and IV from input parameters
					    std::string EncryptionDecryptionPassword = GetEncryptionDecryptionPassword();
					    
						if (EVP_BytesToKey(cipher, EVP_sha256(), nullptr, (const unsigned char*)EncryptionDecryptionPassword.c_str(), EncryptionDecryptionPassword.length(), 1, key, iv) != KEY_SIZE) 
						{
							snprintf(msg,buff_size_config,"DecryptFile_Failure_6");
							Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
							bErrorOccured = true;
						}
						else
						{
							//function for decryption operations
							if (EVP_DecryptInit_ex(ctx, nullptr, nullptr, key, iv) != 1) 
							{
								snprintf(msg,buff_size_config,"DecryptFile_Failure_8");
								Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
								bErrorOccured = true;
							}
							else
							{
								//Read the encrypted input file and write the decrypted contents in the output file
								unsigned char ReadBuffer[READ_BUFFER_SIZE];
								unsigned char WriteBuffer[READ_BUFFER_SIZE * 2];

								int bytes_read = 0;
								int bytes_written = 0;
								while ( (bytes_read = in_file.read(reinterpret_cast<char*>(ReadBuffer), READ_BUFFER_SIZE).gcount() ) > 0 )  
								{
									if (EVP_DecryptUpdate(ctx, WriteBuffer, &bytes_written, ReadBuffer, bytes_read) != 1) 
									{
										snprintf(msg,buff_size_config,"DecryptFile_Failure_9");
										Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
										bErrorOccured = true;
										break;
									}
									out_file.write(reinterpret_cast<char*>(WriteBuffer), bytes_written);
								}


								if (EVP_DecryptFinal_ex(ctx, WriteBuffer, &bytes_written) != 1) 
								{
									snprintf(msg,buff_size_config,"DecryptFile_Failure_10");
									Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
									bErrorOccured = true;
								}
								else
								{
									out_file.write(reinterpret_cast<char*>(WriteBuffer), bytes_written);
								}
							}
						}
					}
				}
			}
			out_file.close();
		}
		in_file.close();
	}

	if(ctx != nullptr)
	{
		EVP_CIPHER_CTX_cleanup(ctx);
		EVP_CIPHER_CTX_free(ctx);
	}
	
	if(bErrorOccured == false)
	{
		bResult = true;
	}
	
	return bResult;
}

/**************************************************************************//**
* \brief   - Encrypt the passed string.
*
* \param   - plaintext: string to be encrypted.	
* \return  - Encrypted string, else empty string if encryption fails.
*
******************************************************************************/
std::string EncryptDecryptData::EncryptString(const std::string &plaintext)
{
    char  msg[buff_size_config] = {0};
    std::string result = "";
    
    //Check if passed string is empty
    if(!plaintext.empty())
    {
		//Create and initialize the encryption context
		EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
		if(ctx == nullptr)
		{
			snprintf(msg,buff_size_config,"EncryptString_Failure_1");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		}
		else
		{
			EVP_CIPHER_CTX_init(ctx);

			//Set encryption parameters
			const EVP_CIPHER* cipher = EVP_aes_256_cbc();
			if(cipher == nullptr)
			{
				snprintf(msg,buff_size_config,"EncryptString_Failure_2");
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
			}
			else
			{	
				unsigned char key[KEY_SIZE] = { 0 }, iv[EVP_MAX_IV_LENGTH] = { 0 };
				// Derive a key and IV from the password
			    std::string EncryptionDecryptionPassword = GetEncryptionDecryptionPassword();
			    
				if (EVP_BytesToKey(cipher, EVP_sha256(), nullptr, (const unsigned char*)EncryptionDecryptionPassword.c_str(), EncryptionDecryptionPassword.length(), 1, key, iv) != KEY_SIZE)
				{			
					snprintf(msg,buff_size_config,"EncryptString_Failure_3");
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
				}
				else
				{		    
					if( EVP_EncryptInit_ex(ctx, cipher, nullptr, key, iv) != 1)
					{
						snprintf(msg,buff_size_config,"EncryptString_Failure_4");
						Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					}
					else
					{	
						//Determine the maximum length of the ciphertext
						int maxCiphertextLen = plaintext.length() + EVP_MAX_BLOCK_LENGTH;
						std::string ciphertext(maxCiphertextLen, '\0');

						//Encrypt the plaintext
						int ciphertextLen = 0;
						if( EVP_EncryptUpdate(ctx, (unsigned char*)ciphertext.data(), &ciphertextLen, (const unsigned char*)plaintext.c_str(), plaintext.length()) != 1)
						{
							snprintf(msg,buff_size_config,"EncryptString_Failure_5");
							Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
						}
						else
						{
							int ciphertextLenFinal = 0;
							if( EVP_EncryptFinal_ex(ctx, (unsigned char*)ciphertext.data() + ciphertextLen, &ciphertextLenFinal) != 1)
							{
								snprintf(msg,buff_size_config,"EncryptString_Failure_6");
								Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
							}
							else
							{
								ciphertextLen += ciphertextLenFinal;  

								//Resize the ciphertext string to the actual ciphertext length
								ciphertext.resize(ciphertextLen);
								
								//Clean up the encryption context
								EVP_CIPHER_CTX_free(ctx);
								
								return ciphertext;
							}
						}
					}
				}
			}			    
			//Clean up the encryption context
			EVP_CIPHER_CTX_free(ctx);
		}
	}
	
	return result;
}

/**************************************************************************//**
* \brief   - Decrypt the passed string.
*
* \param   - ciphertext: already encrypted string that needs to be decrypted.	
* \return  - Decrypted string, else empty string if decryption fails.
*
******************************************************************************/
std::string EncryptDecryptData::DecryptString(const std::string &ciphertext)
{
    std::string result = "";
    char  msg[buff_size_config] = {0};
    
    if(!ciphertext.empty())
    {
	    //Create and initialize the decryption context
	    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();    
	    if(ctx == nullptr)
	    {
	    	snprintf(msg,buff_size_config,"DecryptString_Failure_1");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	    }
	    else
	    {
		    EVP_CIPHER_CTX_init(ctx);   
		    //Set decryption parameters
		    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
		    if(cipher == nullptr)
		    {
		    	snprintf(msg,buff_size_config,"DecryptString_Failure_2");
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		    }
		    else
		    {	    
		    	// Derive a key and IV from the password
   			 	unsigned char key[KEY_SIZE] = { 0 }, iv[EVP_MAX_IV_LENGTH] = { 0 };
   			    std::string EncryptionDecryptionPassword = GetEncryptionDecryptionPassword();
   			 
    			if (EVP_BytesToKey(cipher, EVP_sha256(), nullptr, (const unsigned char*)EncryptionDecryptionPassword.c_str(), EncryptionDecryptionPassword.length(), 1, key, iv) != KEY_SIZE)
    			{
        		       snprintf(msg,buff_size_config,"DecryptString_Failure_3");
        		       Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
    			}
    			else
    			{		
					if( EVP_DecryptInit_ex(ctx, cipher, nullptr, key, iv) != 1)
					{
						snprintf(msg,buff_size_config,"DecryptString_Failure_4");
						Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					}
					else
					{
						//Determine the maximum length of the plaintext
						int maxPlaintextLen = ciphertext.length() + EVP_MAX_BLOCK_LENGTH;
						std::string plaintext(maxPlaintextLen, '\0');
	
						//Decrypt the ciphertext
						int plaintextLen = 0;
						if( EVP_DecryptUpdate(ctx, (unsigned char*)plaintext.data(), &plaintextLen, (const unsigned char*)ciphertext.c_str(), ciphertext.length()) != 1)
						{
							snprintf(msg,buff_size_config,"DecryptString_Failure_5");
							Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
						}
						else
						{
							int plaintextLenFinal = 0;
							if( EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext.data() + plaintextLen, &plaintextLenFinal) != 1)
							{
								snprintf(msg,buff_size_config,"DecryptString_Failure_6");
								Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
							}
							else
							{
								plaintextLen += plaintextLenFinal;
	
								//Clean up the decryption context
								EVP_CIPHER_CTX_free(ctx);
							   
								//Resize the plaintext string to the actual plaintext length
								plaintext.resize(plaintextLen);
								return plaintext;
							}
						}
					}
			    }
		    
		    	//Clean up the decryption context
				EVP_CIPHER_CTX_free(ctx);
			}
	    }
	}

    return result;
}


/**************************************************************************//**
* \brief   - Encrypt the passed TCP/IP data .
*
* \param   - plaintext: data to be encrypted.
* 		   - plaintext_len: length of input data
* 		   - ciphertext: pointer of returning Encrypted data
*
* \return  - Size of Encrypted data.
*
******************************************************************************/
int EncryptDecryptData::EncryptTCPIPStreamData(unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext)
{
	char  msg[buff_size_config] = {0};
    int len = 0, ciphertext_len = 0;
    unsigned char key[KEY_SIZE] = { 0 };
	unsigned char iv[EVP_MAX_IV_LENGTH] = { 0 };
	
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

	if(ctx == nullptr)
	{
		snprintf(msg,buff_size_config,"TCP/IP Encrypt_Failure_1");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	else
	{
	    EVP_CIPHER_CTX_init(ctx);
		//Set encryption parameters
	    
		const EVP_CIPHER* cipher = EVP_aes_256_cbc();
		if(cipher == nullptr)
		{
			snprintf(msg,buff_size_config,"TCP/IP Encrypt_Failure_2");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		}
		
	    std::string EncryptionPassword = GetDataStreamingEncryptionPassword();
	    
		if (EVP_BytesToKey(cipher, EVP_sha256(), nullptr, (const unsigned char*)EncryptionPassword.c_str(), EncryptionPassword.length(), 1, key, iv) != KEY_SIZE)
		{			
			snprintf(msg,buff_size_config,"TCP/IP Encrypt_Failure_3");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		}
		else
		{
			EVP_CIPHER_CTX_set_padding(ctx, 1); // 1 = enable padding
		    if (EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv) != 1)
		    {
				snprintf(msg,buff_size_config,"TCPIP Encrypt_Failure_4");
				Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		    }
		    else
		    {
		    	len = 0;
		        if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1)
		        {
		    		snprintf(msg,buff_size_config,"TCPIP Encrypt_Failure_5");
		    		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		        }
		        else
		        {
		            ciphertext_len = len;
		            if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
		            {
		        		snprintf(msg,buff_size_config,"TCPIP Encrypt_Failure_6");
		        		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		            }
		            ciphertext_len += len;
		            EVP_CIPHER_CTX_free(ctx);
		            return ciphertext_len;
		        }
		    }
		}
	}
    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}
/**************************************************************************//**
* \brief   - Function to convert a string to a hex string
*
* \param   - data - encrypted string to be convert in to hex.	
* \return  - hex string, else empty string if hex conversion fails.
*
******************************************************************************/
std::string EncryptDecryptData::ConvertEncryptedDataToHexString(const std::string& data)
{
	std::ostringstream oss;
	for (unsigned char c : data) 
	{
		oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
	}
	return oss.str();
}

/**************************************************************************//**
* \brief   - convert a hex string to a string of original Data (Encrypted data)
*
* \param   - hex - hex string that needs to be convert back to original string.	
* \return  - encrypted or original string, else empty string if fails.
*
******************************************************************************/
std::string EncryptDecryptData::ConvertHexToEncryptedData(const std::string& hex)
{
    std::string result;
    for (size_t i = 0; i < hex.length(); i += 2) 
    {
        std::string byteString = hex.substr(i, 2);
        char byte = static_cast<char>(strtol(byteString.c_str(), nullptr, 16));
        result.push_back(byte);
    }
    return result;
}
	
