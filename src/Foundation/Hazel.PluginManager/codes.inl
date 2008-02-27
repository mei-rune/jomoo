
tstring encode (const tstring &input)
{
	tstring result;
	result.reserve (input.size ());
	for (const char *s = input.c_str (); *s; ++s)
		if (strchr (SAFE, *s))
			result += *s;
		else
		{
			result += '%';
			result += HEX [((unsigned char) *s >> 4) & 0xf];
			result += HEX [((unsigned char) *s     ) & 0xf];
		}
		return result;
}

tstring decode (const tstring &input)
{
	tstring result;
	result.reserve (input.size ());
	for (const char *s = input.c_str (); *s; ++s)
		if (strchr (SAFE, *s))
			result += *s;
		else if (*s == '%' && isxdigit (s[1]) && isxdigit (s[2]))
		{
			result += (char) (((strchr (HEX, tolower (s[1])) - HEX) << 4)
				+ ((strchr (HEX, tolower (s[2])) - HEX)));
			s += 2;
		}
		else
			ThrowException1( RuntimeException, "不可识别的字符");

		return result;
}

