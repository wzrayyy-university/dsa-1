import itertools


def find_number(a):
    date = 0
    points = 0
    for item in a:
        date += item["time_complexity"]
        points += item["deadline"] - date
    return points


def main():
    size = int(input())
    a = []

    for _ in range(size):
        val = input().split(' ')
        a.append({'time_complexity': int(val[0]), 'deadline': int(val[1])})

    max_number = -999999999999999999999999999999999999
    max_perm = {}
    for x in itertools.permutations(a):
        number = find_number(x)
        if number >= max_number:
            max_number = number
            if number not in max_perm:
                max_perm[number] = []
            max_perm[number].append(x)

    print(max_number)
    for x in max_perm[max_number]:
        print(x)


if __name__ == "__main__":
    main()
