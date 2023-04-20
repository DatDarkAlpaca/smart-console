#pragma once

namespace dat
{
	template<typename T, typename ByteSize>
	struct DataRead
	{
		T data;
		DWORD dataLength;
	};
}