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

#ifndef HLPSHA2_512_224_H
#define HLPSHA2_512_224_H

#include "HlpSHA2_512Base.h"


class SHA2_512_224 : public SHA2_512Base
{
public:
	SHA2_512_224()
		: SHA2_512Base(28)
	{
		name = __func__;
	} // end constructor

	virtual void Initialize()
	{
		state.get()[0] = 0x8C3D37C819544DA2;
		state.get()[1] = 0x73E1996689DCD4D6;
		state.get()[2] = 0x1DFAB7AE32FF9C82;
		state.get()[3] = 0x679DD514582F9FCF;
		state.get()[4] = 0x0F6D2B697BD44DA8;
		state.get()[5] = 0x77E36F7304C48942;
		state.get()[6] = 0x3F9D85A86A1D36C8;
		state.get()[7] = 0x1112E6AD91D692A1;

		SHA2_512Base::Initialize();
	} // end function Initialize

protected:
	virtual HashLibByteArray GetResult()
	{
		HashLibByteArray result = HashLibByteArray(4 * sizeof(uint64_t));
		Converters::be64_copy(&state.get()[0], 0, &result[0], 0, (int32_t)result.size());
		result.resize(GetHashSize() * sizeof(uint8_t));

		return result;
	} // end function GetResult

}; // end class SHA2_512_224


#endif //!HLPSHA2_512_224_H