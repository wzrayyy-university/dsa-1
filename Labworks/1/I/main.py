def solution(start, stop, debug=False):
    one = 0
    zero = 0
    length = len(bin(start)) - 2

    if len(bin(stop)) - 2 == 1 or len(bin(stop)) - 2 == 2:
        return 0

    for i in bin(start)[2:]:
        if i == '1' and zero == 0:
            one += 1
        elif i == '0':
            zero += 1
        else:
            break

    # first iteration
    number = '1' * one + '0' * zero + '1' * (length - one - zero)
    counter = 0
    if int(number, 2) == stop:
        return 1
    elif int(number, 2) < stop:
        if len(number) > 3:
            counter += 1
            if debug:
                print(number, int(number, 2))
    else:
        return 0

    while int(number, 2) < stop:
        zero -= 1
        if zero == 0:
            one += 1
            zero = length - one - 1
        if one >= length - 1:
            length += 1
            one = 1
            zero = length - one - 1
        number = '1' * one + '0' * zero + '1' * (length - one - zero)
        if len(number) < 3:
            continue

        if number.split('0')[0] != number:
            if debug:
                print(number, int(number, 2))
            counter += 1

    if int(number, 2) > stop:
        counter -= 1

    return counter


def test():
    input_data: list[tuple[int, int]] = [
        # (259, 263),
        # (259, 264),
        # (16384, 65536),
        # (16385, 16385),
        # (16385, 16386),
        # (259, 16387),
        (1, 10000000000)
        # (1, 16)
    ]

    for data in input_data:
        print(solution(*data, debug=True))


def main():
    start, stop = map(int, input().split())
    print(solution(start, stop))


test()

