//from google protobuf


// -------------------------------------------------------------------
// Token-parsing helpers.  Remember that these don't need to report
// errors since any errors should already have been reported while
// tokenizing.  Also, these can assume that whatever text they
// are given is text that the tokenizer actually parsed as a token
// of the given type.

bool Tokenizer::ParseInteger(const string& text, uint64 max_value, uint64* output) {
 // Sadly, we can't just use strtoul() since it is only 32-bit and strtoull()
 // is non-standard.  I hate the C standard library.  :(
 //  return strtoull(text.c_str(), NULL, 0);

	const char* ptr = text.c_str();
	int base = 10;
	if (ptr[0] == '0') {
		if (ptr[1] == 'x' || ptr[1] == 'X') {
			// This is hex.
			base = 16;
			ptr += 2;
		} else {
			// This is octal.
			base = 8;
		}
	}

	uint64 result = 0;
	for (; *ptr != '\0'; ptr++) {
		int digit = DigitValue(*ptr);
		GOOGLE_LOG_IF(DFATAL, digit < 0 || digit >= base)
			<< " Tokenizer::ParseInteger() passed text that could not have been"
			" tokenized as an integer: " << CEscape(text);
		if (digit > max_value || result > (max_value - digit) / base) {
			// Overflow.
			return false;
		}
		result = result * base + digit;
	}

	*output = result;
	return true;
}

double Tokenizer::ParseFloat(const string& text) {
	const char* start = text.c_str();
	char* end;
	double result = NoLocaleStrtod(start, &end);

	// "1e" is not a valid float, but if the tokenizer reads it, it will
	// report an error but still return it as a valid token.  We need to
	// accept anything the tokenizer could possibly return, error or not.
	if (*end == 'e' || *end == 'E') {
		++end;
		if (*end == '-' || *end == '+') ++end;
	}

	// If the Tokenizer had allow_f_after_float_ enabled, the float may be
	// suffixed with the letter 'f'.
	if (*end == 'f' || *end == 'F') {
		++end;
	}

	GOOGLE_LOG_IF(DFATAL, end - start != text.size() || *start == '-')
		<< " Tokenizer::ParseFloat() passed text that could not have been"
		" tokenized as a float: " << CEscape(text);
	return result;
}
