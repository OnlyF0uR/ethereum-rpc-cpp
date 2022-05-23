// Arbitrary precision base conversion by Daniel Gehriger <gehriger@linkcad.com>   
#ifndef BASE_CONVERTER_H
#define BASE_CONVERTER_H
#include <stdexcept>
#include <algorithm>
#include <string>

class BaseConverter
{
public:
	std::string GetSourceBaseSet() const { return sourceBaseSet_; }
	std::string GetTargetBaseSet() const { return targetBaseSet_; }
	unsigned int GetSourceBase() const { return (unsigned int)sourceBaseSet_.length(); }
	unsigned int GetTargetBase() const { return (unsigned int)targetBaseSet_.length(); }

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="sourceBaseSet">Characters used for source base</param>
	/// <param name="targetBaseSet">Characters used for target base</param>
	BaseConverter(const std::string& sourceBaseSet, const std::string& targetBaseSet);

	/// <summary>
	/// Get a base converter for decimal to binary numbers
	/// </summary>
	static const BaseConverter& DecimalToBinaryConverter();

	/// <summary>
	/// Get a base converter for binary to decimal numbers
	/// </summary>
	static const BaseConverter& BinaryToDecimalConverter();

	/// <summary>
	/// Get a base converter for decimal to binary numbers
	/// </summary>
	static const BaseConverter& DecimalToHexConverter();

	/// <summary>
	/// Get a base converter for binary to decimal numbers
	/// </summary>
	static const BaseConverter& HexToDecimalConverter();

	/// <summary>
	/// Convert a value in the source number base to the target number base.
	/// </summary>
	/// <param name="value">Value in source number base.</param>
	/// <returns>Value in target number base.</returns>
	std::string  Convert(std::string value) const;


	/// <summary>
	/// Convert a value in the source number base to the target number base.
	/// </summary>
	/// <param name="value">Value in source number base.</param>
	/// <param name="minDigits">Minimum number of digits for returned value.</param>
	/// <returns>Value in target number base.</returns>
	std::string Convert(const std::string& value, size_t minDigits) const;

	/// <summary>
	/// Convert a decimal value to the target base.
	/// </summary>
	/// <param name="value">Decimal value.</param>
	/// <returns>Result in target base.</returns>
	std::string FromDecimal(unsigned int value) const;

	/// <summary>
	/// Convert a decimal value to the target base.
	/// </summary>
	/// <param name="value">Decimal value.</param>
	/// <param name="minDigits">Minimum number of digits for returned value.</param>
	/// <returns>Result in target base.</returns>
	std::string FromDecimal(unsigned int value, size_t minDigits) const;

	/// <summary>
	/// Convert value in source base to decimal.
	/// </summary>
	/// <param name="value">Value in source base.</param>
	/// <returns>Decimal value.</returns>
	unsigned int ToDecimal(std::string value) const;

private:
	/// <summary>
	/// Divides x by y, and returns the quotient and remainder.
	/// </summary>
	/// <param name="baseDigits">Base digits for x and quotient.</param>
	/// <param name="x">Numerator expressed in base digits; contains quotient, expressed in base digits, upon return.</param>
	/// <param name="y">Denominator</param>
	/// <returns>Remainder of x / y.</returns>
	static unsigned int divide(const std::string& baseDigits,
		std::string& x,
		unsigned int y);

	static unsigned int base2dec(const std::string& baseDigits,
		const std::string& value);

	static std::string dec2base(const std::string& baseDigits, unsigned int value);

private:
	static const char* binarySet_;
	static const char* decimalSet_;
	static const char* hexSet_;
	std::string         sourceBaseSet_;
	std::string         targetBaseSet_;
};

const char* BaseConverter::binarySet_ = "01";
const char* BaseConverter::decimalSet_ = "0123456789";
const char* BaseConverter::hexSet_ = "0123456789ABCDEF";

BaseConverter::BaseConverter(const std::string& sourceBaseSet, const std::string& targetBaseSet)
	: sourceBaseSet_(sourceBaseSet)
	, targetBaseSet_(targetBaseSet)
{
	if (sourceBaseSet.empty() || targetBaseSet.empty())
		throw std::invalid_argument("Invalid base character set");
}

const BaseConverter& BaseConverter::DecimalToBinaryConverter()
{
	static const BaseConverter dec2bin(decimalSet_, binarySet_);
	return dec2bin;
}

const BaseConverter& BaseConverter::BinaryToDecimalConverter()
{
	static const BaseConverter bin2dec(binarySet_, decimalSet_);
	return bin2dec;
}

const BaseConverter& BaseConverter::DecimalToHexConverter()
{
	static const BaseConverter dec2hex(decimalSet_, hexSet_);
	return dec2hex;
}

const BaseConverter& BaseConverter::HexToDecimalConverter()
{
	static const BaseConverter hex2dec(hexSet_, decimalSet_);
	return hex2dec;
}

std::string BaseConverter::Convert(std::string value) const
{
	unsigned int numberBase = GetTargetBase();
	std::string result;

	do
	{
		unsigned int remainder = divide(sourceBaseSet_, value, numberBase);
		result.push_back(targetBaseSet_[remainder]);
	} while (!value.empty() && !(value.length() == 1 && value[0] == sourceBaseSet_[0]));

	std::reverse(result.begin(), result.end());
	return result;
}

std::string BaseConverter::Convert(const std::string& value, size_t minDigits) const
{
	std::string result = Convert(value);
	if (result.length() < minDigits)
		return std::string(minDigits - result.length(), targetBaseSet_[0]) + result;
	else
		return result;
}

std::string BaseConverter::FromDecimal(unsigned int value) const
{
	return dec2base(targetBaseSet_, value);
}

std::string BaseConverter::FromDecimal(unsigned int value, size_t minDigits) const
{
	std::string result = FromDecimal(value);
	if (result.length() < minDigits)
		return std::string(minDigits - result.length(), targetBaseSet_[0]) + result;
	else
		return result;
}

unsigned int BaseConverter::ToDecimal(std::string value) const
{
	return base2dec(sourceBaseSet_, value);
}

unsigned int BaseConverter::divide(const std::string& baseDigits, std::string& x, unsigned int y)
{
	std::string quotient;

	size_t lenght = x.length();
	for (size_t i = 0; i < lenght; ++i)
	{
		size_t j = i + 1 + x.length() - lenght;
		if (x.length() < j)
			break;

		unsigned int value = base2dec(baseDigits, x.substr(0, j));

		quotient.push_back(baseDigits[value / y]);
		x = dec2base(baseDigits, value % y) + x.substr(j);
	}

	// calculate remainder
	unsigned int remainder = base2dec(baseDigits, x);

	// remove leading "zeros" from quotient and store in 'x'
	size_t n = quotient.find_first_not_of(baseDigits[0]);
	if (n != std::string::npos)
	{
		x = quotient.substr(n);
	}
	else
	{
		x.clear();
	}

	return remainder;
}

std::string BaseConverter::dec2base(const std::string& baseDigits, unsigned int value)
{
	unsigned int numberBase = (unsigned int)baseDigits.length();
	std::string result;
	do
	{
		result.push_back(baseDigits[value % numberBase]);
		value /= numberBase;
	} while (value > 0);

	std::reverse(result.begin(), result.end());
	return result;
}

unsigned int BaseConverter::base2dec(const std::string& baseDigits, const std::string& value)
{
	unsigned int numberBase = (unsigned int)baseDigits.length();
	unsigned int result = 0;
	for (size_t i = 0; i < value.length(); ++i)
	{
		result *= numberBase;
		int c = baseDigits.find(value[i]);
		if (c == std::string::npos)
			throw std::runtime_error("Invalid character");

		result += (unsigned int)c;
	}

	return result;
}
#endif