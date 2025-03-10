import time

import requests

import config

verdicts = {4: '+', 2: '-', 3: '=='}
last_time = time.time()


def make_request(code, check_for_ans=False, target_idx=None):
    while True:
        global last_time
        last_time = time.time()
        time.sleep(20.1 - time.time() + last_time)  # timeout to bypass cloudflare filters
        request = requests.post('https://api.sort-me.org/submit', headers=config.HEADERS,
                                json={"task_id": config.TASK_ID, "lang": "python", "code": code, "contest_id": config.CONTEST_ID})
        if request.status_code == 201:
            solution_id = request.json()['id']
            break

    while True:
        response = requests.get('https://api.sort-me.org/getSubmissionInfo', headers=config.HEADERS,
                                params={'id': solution_id})
        if response.status_code == 200:
            try:
                if check_for_ans:
                    return response.json()['subtasks'][0]['failed_tests'][0]['n'] == target_idx + 1

                return response.json()['subtasks'][0]['failed_tests'][0]['verdict']
            except Exception:
                time.sleep(2)


class Executor:
    def __init__(self):
        self.answers = []

    def generate_ifs_(self, additional_element):
        code = ''
        for ans in self.answers:
            code += f'\nif element == {ans[0]}:\n\tprint("{ans[1]}")\n\texit(0)\n'
        if additional_element != None:
            code += f'\nif element == {additional_element[0]}:\n\tprint("{additional_element[1]}")\n\texit(0)\n'
        return code

    def generate_code_(self, target, additional_element=None):
        code = f'import time\ntarget = {target}\n\nn = int(input())\n\na = [int(x) for x in input().strip().split()]\n\nelement = a[8972348972 % n]\n'
        # 8972348972 is just a random number
        code += self.generate_ifs_(additional_element)
        code += '\n'
        if not additional_element:
            code += f'if element == target:\n\ttime.sleep(100)\nelif element < target:\n\texit(0)\nelif element > target:\n\texit(1)'
        return code

    def search(self):
        while True:
            left, right = -(2 * (10 ** 9)), 2 * (10 ** 9)
            iters = 0
            while right + 1 > left:
                iters += 1
                mid = (left + right) // 2
                verdict = make_request(self.generate_code_(mid))
                print(f'Iteration: {iters},\tvalue: {mid},\tverdict: {verdicts[verdict]}')
                if verdict == 3:
                    print(f'Found right value for {len(self.answers) + 1}')
                    is_yes = make_request(self.generate_code_(mid, additional_element=[mid, 'YES']),
                                          target_idx=len(self.answers) + 1, check_for_ans=True)
                    if is_yes:
                        self.answers.append([mid, 'YES'])
                        print('Answer is: YES')
                    else:
                        self.answers.append([mid, 'NO'])
                        print('Answer is: NO')
                    print(f'Answers: {self.answers}\n')
                    break
                elif verdict == 4:
                    left = mid + 1
                elif verdict == 2:
                    right = mid - 1


def main():
    ex = Executor()
    print(ex.search())


if __name__ == "__main__":
    main()
