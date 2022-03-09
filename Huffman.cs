using System;
using System.Runtime.InteropServices;

[DllImport("HuffmanEncryption.dll")]
internal static extern void HuffmanEncode(IntPtr huffdata, int hufflength, IntPtr dataresult, ref int resultlength);
[DllImport("HuffmanEncryption.dll")]
internal static extern void HuffmanDecode(IntPtr huffdata, int hufflength, IntPtr dataresult, ref int resultlength);

// Perform huffman encryption if necessary
private static byte[] HuffmanEncode(bool encode, byte[] data)
{
	// Nothing to do?
	if(data == null || data.Length == 0) return null;

	// Allocate memory for result
	int length = data.Length * 2;
	byte[] dataresult = new byte[length];

	// Keep it pinned in memory so random
	// garbage collection doesn't move it,
	// resulting in unpredictable AccessViolationException
	GCHandle dataHandle = GCHandle.Alloc(data, GCHandleType.Pinned);
	GCHandle resultHandle = GCHandle.Alloc(dataresult, GCHandleType.Pinned);

	try
	{
		// Perform huffman
		if(encode) HuffmanEncode(dataHandle.AddrOfPinnedObject(), data.Length, resultHandle.AddrOfPinnedObject(), ref length);
		else HuffmanDecode(dataHandle.AddrOfPinnedObject(), data.Length, resultHandle.AddrOfPinnedObject(), ref length);
	}
	finally
	{
		// Put data back into managed memory
		dataHandle.Free();
		resultHandle.Free();
	}

	// Resize the result and return
	Array.Resize(ref dataresult, length);
	return dataresult;
}