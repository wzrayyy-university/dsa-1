import dataclasses

@dataclasses.dataclass
class Segment:
    l: float
    r: float

def find_alphabet(s: str) -> list[str]:
    alphabet = []
    for x in s:
        if x not in alphabet:
            alphabet.append(x)
    return alphabet

def find_probabilities(s: str, alphabet: list[str]) -> dict[str, Segment]:
    count: dict[str, int] = {}
    for x in s:
        if x not in count:
            count[x] = 0
        count[x] += 1

    left = 0.0
    slice = 1.0 / len(s)
    segments: dict[str, Segment] = {}

    for x in sorted(alphabet):
        segments[x] = Segment(left,left + (slice * count[x]))
        left += slice * count[x]

    return segments


def arithmetic_coding(s: str) -> float:
    alphabet = find_alphabet(s)
    probabilities = find_probabilities(s, alphabet)

    left = 0.0
    right = 1.0

    for x in s:
        new_left = left + (right - left) * probabilities[x].l
        new_right = left + (right - left) * probabilities[x].r

        left = new_left
        right = new_right

    return left




def main():
    s = input()
    print(round(arithmetic_coding(s), 6))


if __name__ == "__main__":
    main()
