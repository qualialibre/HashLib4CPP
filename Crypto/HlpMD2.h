// ///////////////////////////////////////////////////////////////// //
// *C++ 11 HashFactory Library                                 
// *Copyright(c) 2018  Mbadiwe Nnaemeka Ronald                 
// *Github Repository <https://github.com/ron4fun>             

// *Distributed under the MIT software license, see the accompanying file LICENSE 
// *or visit http ://www.opensource.org/licenses/mit-license.php.           

// *Acknowledgements:                                  
// ** //
// *Thanks to Ugochukwu Mmaduekwe (https://github.com/Xor-el) for his creative        
// *development of this library in Pascal/Delphi                         

// ////////////////////////////////////////////////////// ///////////////

#ifndef HLPMD2_H
#define HLPMD2_H

#include "../Base/HlpHashCryptoNotBuildIn.h"


class MD2 : public BlockHash, public IICryptoNotBuildIn, public IITransformBlock
{
public:
	MD2()
		: BlockHash(16, 16)
	{
		name = __func__;

		temp = shared_ptr<uint8_t>(new uint8_t[48], default_delete<uint8_t[]>());
		state = make_shared<HashLibByteArray>(16);
		checksum = make_shared<HashLibByteArray>(16);
	} // end constructor

	~MD2()
	{
		//delete[] temp;
		//delete state;
		//delete checksum;
	} // end destructor

	virtual void Initialize()
	{
		memset(&(*state)[0], 0, 16 * sizeof(uint8_t));
		memset(&(*checksum)[0], 0, 16 * sizeof(uint8_t));

		BlockHash::Initialize();
	} // end function Initialize

protected:
	virtual void Finish()
	{
		uint32_t padLen;

		padLen = 16 - buffer->GetPos();
		HashLibByteArray pad = HashLibByteArray(padLen);

		register uint32_t i = 0;
		while (i < padLen)
		{
			pad[i] = padLen;
			i++;
		} // end while
		
		TransformBytes(pad, 0, padLen);
		TransformBytes(*checksum, 0, 16);

	} // end function Finish

	virtual HashLibByteArray GetResult()
	{
		return *state;
	} // end function GetResult
		
	virtual void TransformBlock(const uint8_t *a_data,
		const int32_t a_data_length, const int32_t a_index)
	{
		register uint32_t t = 0;

		memmove(&temp.get()[0], &(*state)[0], 16);
		memmove(&temp.get()[16], &a_data[a_index], 16);

		for (register uint32_t i = 0; i < 16; i++)
		{
			temp.get()[i + 32] = (uint8_t)((*state)[i] ^ a_data[i + a_index]);
		} // end for
			
		for (register uint32_t i = 0; i < 18; i++)
		{
			for (register uint32_t j = 0; j < 48; j++)
			{
				temp.get()[j] = (uint8_t)(temp.get()[j] ^ pi[t]);
				t = temp.get()[j];
			} // end for

			t = (uint8_t)(t + i);
		} // end for

		memmove(&(*state)[0], &temp.get()[0], 16);

		t = (*checksum)[15];

		for (register uint32_t i = 0; i < 16; i++)
		{
			(*checksum)[i] = (*checksum)[i] ^ (pi[a_data[i + a_index] ^ t]);
			t = (*checksum)[i];
		} // end for
		
		memset(&temp.get()[0], 0, 48);
	} // end function TransformBlock

private:
	shared_ptr<HashLibByteArray> state;
	shared_ptr<HashLibByteArray> checksum;
	shared_ptr<uint8_t> temp;

	static const uint8_t pi[256];


}; // end class MD2

const uint8_t MD2::pi[256] = {41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
				19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188, 76, 130, 202,
				30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24, 138, 23, 229, 18,	190, 78,
				196, 214, 218, 158, 222, 73, 160, 251, 245, 142, 187, 47, 238, 122, 169, 104, 121,
				145, 21, 178, 7, 63, 148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144,
				50, 39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165, 181, 209, 215,
				94, 146, 42, 172, 86, 170, 198,	79, 184, 56, 210, 150, 164, 125, 182, 118, 252, 107, 
				226, 156, 116, 4, 241, 69, 157, 112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45,
				168, 2,	27, 96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15, 85, 71,
				163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197, 234, 38, 44, 83, 13, 110, 133,
				40, 132, 9, 211, 223, 205, 244, 65, 129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 
				36, 225, 123, 8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233, 203, 213,
				254, 59, 0, 29, 57,	242, 239, 183, 14, 102, 88, 208, 228, 166, 119, 114, 248, 235, 117,
				75, 10,	49, 68, 80, 180, 143, 237, 31, 26, 219, 153, 141, 51, 159, 17, 131, 20};


#endif // !HLPMD2_H