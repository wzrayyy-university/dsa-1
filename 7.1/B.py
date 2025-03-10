def lz78(string: str) -> None:
    buffer = ''
    enc_dict: dict[str, int] = {}
    for char in string:
        comb = buffer + char
        if comb in enc_dict:
            buffer += char
        else:
            if buffer in enc_dict:
                print(enc_dict[buffer], char)
            else:
                print(0, char)
            enc_dict[comb] = len(enc_dict) + 1
            buffer = ""

    if buffer:
        if buffer in enc_dict:
            print(str(enc_dict[buffer]) + ' \0')
        else:
            print(enc_dict[buffer[:-1]], buffer[-1])



def main():
    s = input()
    lz78(s)

if __name__ == "__main__":
    main()

