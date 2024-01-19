using System;
using System.Security.Cryptography;

if (args is { Length: > 0 })
{
    Console.WriteLine(Totp.Compute(args[0]));
}
else
{
    Console.WriteLine("Please specify the token used to compute totp code");
    return;
}

/// <summary>
/// Time-Based One-Time Password
/// https://datatracker.ietf.org/doc/html/rfc6238
/// </summary>
public static class Totp
{
    private const int CodeSize = 6;
    private const int Base = 1000_000;

    /// <summary>
    /// Compute totp
    /// </summary>
    /// <param name="securityToken">base32 encoded token/secret</param>
    /// <returns>computed totp code</returns>
    public static string Compute(string securityToken) => Compute(Base32EncodeHelper.GetBytes(securityToken), GetCurrentTimeStepNumber());

    private static string Compute(byte[] securityToken, long counter)
    {
        using HMAC hmac = new HMACSHA1(securityToken);
        var stepBytes = BitConverter.GetBytes(counter);
        if (BitConverter.IsLittleEndian)
        {
            Array.Reverse(stepBytes); // need BigEndian
        }
        // See https://tools.ietf.org/html/rfc4226
        var hashResult = hmac.ComputeHash(stepBytes);

        var offset = hashResult[^1] & 0xf;
        var p = $"{hashResult[offset]:X2}{hashResult[offset + 1]:X2}{hashResult[offset + 2]:X2}{hashResult[offset + 3]:X2}";
        var num = Convert.ToInt64(p, 16) & 0x7FFFFFFF;
        var code = (num % Base).ToString();
        return code.PadLeft(CodeSize, '0');
    }

    /// <summary>
    /// time step
    /// 30s(Recommend)
    /// </summary>
    public const int TimeStepSeconds = 30;

    // More info: https://tools.ietf.org/html/rfc6238#section-4
    private static long GetCurrentTimeStepNumber() => DateTimeOffset.UtcNow.ToUnixTimeSeconds() / TimeStepSeconds;
}

/// <summary>
/// Base32Encode
/// https://stackoverflow.com/questions/641361/base32-decoding/7135008#7135008
/// </summary>
public static class Base32EncodeHelper
{
    /// <summary>
    /// Standard Base32 characters
    /// https://www.rfc-editor.org/rfc/rfc4648#section-6
    /// </summary>
    public static readonly char[] Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567".ToCharArray();

    public static byte[] GetBytes(string base32String, char paddingChar = '=')
    {
        base32String = base32String.Trim(paddingChar); //remove padding characters
        var byteCount = base32String.Length * 5 / 8; //this must be TRUNCATED
        var returnArray = new byte[byteCount];

        byte curByte = 0, bitsRemaining = 8;
        var arrayIndex = 0;
        foreach (var c in base32String)
        {
            var cValue = CharToValue(c);

            int mask;
            if (bitsRemaining > 5)
            {
                mask = cValue << (bitsRemaining - 5);
                curByte = (byte)(curByte | mask);
                bitsRemaining -= 5;
            }
            else
            {
                mask = cValue >> (5 - bitsRemaining);
                curByte = (byte)(curByte | mask);
                returnArray[arrayIndex++] = curByte;
                curByte = (byte)(cValue << (3 + bitsRemaining));
                bitsRemaining += 3;
            }
        }

        //if we didn't end with a full byte
        if (arrayIndex != byteCount)
        {
            returnArray[arrayIndex] = curByte;
        }

        return returnArray;
    }

    private static int CharToValue(char c)
    {
        var value = (int)c;
        return value switch
        {
            //65-90 == uppercase letters
            < 91 and > 64 => value - 65,
            //50-55 == numbers 2-7
            < 56 and > 49 => value - 24,
            //97-122 == lowercase letters
            < 123 and > 96 => value - 97,
            _ => throw new ArgumentException(@"Character is not a Base32 character.", nameof(c))
        };
    }
}
