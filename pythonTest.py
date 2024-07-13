import subprocess
import filecmp
import os

def run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout):
    try:
        with open(input_path, 'r') as input_file:
            with open(output_path, 'w') as output_file:
                subprocess.run([exe_path], stdin=input_file, stdout=output_file, timeout=timeout)
                valgrind_process = subprocess.run(['valgrind', '--leak-check=full', '--log-file=' + valgrind_output_path, exe_path], stdin=input_file, stderr=subprocess.PIPE, timeout=timeout)
    except subprocess.TimeoutExpired:
        print(f"{os.path.basename(input_path)}: TIMED OUT")
        return False, False

    output_passed = filecmp.cmp(test_output_path, output_path)

    with open(valgrind_output_path, 'r') as valgrind_output_file:
        valgrind_output = valgrind_output_file.read()

    memory_passed = "ERROR SUMMARY: 0 errors" in valgrind_output

    return output_passed, memory_passed

def run_levelA(exe_path):
    timeout = 10
    for i in range(1, 11):
        input_prefix = "input/testLevelA"
        output_prefix = "output/TestLevelA"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/TestLevelA{i}.out"
        valgrind_output_path = f"valgrindOutput/TestLevelA{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testLevelA {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testLevelA {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testLevelA {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testLevelA {i}: FAILED, MEMORY: FAILED")

def run_levelAPlus(exe_path):
    timeout = 15
    for i in range(1, 50):
        input_prefix = "input/testLevelAPlus"
        output_prefix = "output/TestLevelAPlus"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/TestLevelAPlus{i}.out"
        valgrind_output_path = f"valgrindOutput/TestLevelAPlus{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testLevelAPlus {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testLevelAPlus {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testLevelAPlus {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testLevelAPlus {i}: FAILED, MEMORY: FAILED")

def run_levelB(exe_path):
    timeout = 15
    for i in range(1, 101):
        input_prefix = "input/testLevelB"
        output_prefix = "output/TestLevelB"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/testLevelB{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelB{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testLevelB {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testLevelB {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testLevelB {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testLevelB {i}: FAILED, MEMORY: FAILED")

def run_levelC(exe_path):
    timeout = 15
    for i in range(1, 51):
        input_prefix = "input/testLevelC"
        output_prefix = "output/TestLevelC"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/testLevelC{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelC{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testLevelC {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testLevelC {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testLevelC {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testLevelC {i}: FAILED, MEMORY: FAILED")

def run_levelD(exe_path):
    timeout = 30
    for i in range(1, 21):
        input_prefix = "input/testLevelD"
        output_prefix = "output/TestLevelD"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/testLevelD{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelD{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testLevelD {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testLevelD {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testLevelD {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testLevelD {i}: FAILED, MEMORY: FAILED")

def run_levelZ(exe_path):
    timeout = 60
    for i in range(1, 11):
        input_prefix = "input/testLevelZ"
        output_prefix = "output/TestLevelZ"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/testLevelZ{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelZ{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testLevelZ {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testLevelZ {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testLevelZ {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testLevelZ {i}: FAILED, MEMORY: FAILED")

def run_BattleTreason(exe_path):
    timeout = 5
    for i in range(1, 41):
        input_prefix = "input/testBattleTreason"
        output_prefix = "output/testBattleTreason"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput/testBattleTreason{i}.out"
        valgrind_output_path = f"valgrindOutput/testBattleTreason{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        if output_passed and memory_passed:
            print(f"testBattleTreason {i}: PASSED, MEMORY: PASSED")
        elif output_passed:
            print(f"testBattleTreason {i}: PASSED, MEMORY: FAILED")
        elif memory_passed:
            print(f"testBattleTreason {i}: FAILED, MEMORY: PASSED")
        else:
            print(f"testBattleTreason {i}: FAILED, MEMORY: FAILED")

if __name__ == "__main__":
    exe_path = "a.exe"
    output_directory = "output"
    valgrind_output_directory = "valgrindOutput"

    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    if not os.path.exists(valgrind_output_directory):
        os.makedirs(valgrind_output_directory)

    print("***************************** Tests Level A (Simple) *****************************")
    run_levelA(exe_path)
    print("***************************** Tests Level A Plus (Easy) *****************************")
    run_levelAPlus(exe_path)
    print("**************************** Tests Level B (Medium) ****************************")
    run_levelB(exe_path)
    print("***************************** Tests Level C (Hard) *****************************")
    run_levelC(exe_path)
    print("***************************** Tests Level D (Impossible) *****************************")
    run_levelD(exe_path)
    print("************************** Tests Level Z (IDK at this point?) **************************")
    run_levelZ(exe_path)
    print("************************** EXTRA battle+ treason Test (Special)  **************************")
    run_BattleTreason(exe_path)
