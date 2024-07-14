import subprocess
import filecmp
import os

import subprocess
import filecmp
import os

def run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout):
    try:
        with open(input_path, 'r') as input_file:
            with open(output_path, 'w') as output_file:
                # Run the executable and redirect input and output
                subprocess.run(
                    [exe_path],
                    stdin=input_file,
                    stdout=output_file,
                    stderr=subprocess.DEVNULL,  # Suppress stderr
                    timeout=timeout
                )

            # Reset input file pointer and run Valgrind with the same input file
            input_file.seek(0)
            valgrind_process = subprocess.run(
                ['valgrind', '--leak-check=full', '--log-file=' + valgrind_output_path, exe_path],
                stdin=input_file,
                stdout=subprocess.DEVNULL,  # Suppress stdout
                stderr=subprocess.DEVNULL,  # Suppress stderr
                timeout=timeout
            )
    except subprocess.TimeoutExpired:
        print(f"{os.path.basename(input_path)}: \033[91mTIMED OUT\033[0m")
        return False, False

    output_passed = filecmp.cmp(test_output_path, output_path)

    with open(valgrind_output_path, 'r') as valgrind_output_file:
        valgrind_output = valgrind_output_file.read()

    memory_passed = "ERROR SUMMARY: 0 errors" in valgrind_output

    return output_passed, memory_passed

def print_result(test_name, index, output_passed, memory_passed):
    if output_passed and memory_passed:
        print(f"{test_name} {index}: \033[92mPASSED\033[0m, MEMORY: \033[92mPASSED\033[0m")
    elif output_passed:
        print(f"{test_name} {index}: \033[92mPASSED\033[0m, MEMORY: \033[91mFAILED\033[0m")
    elif memory_passed:
        print(f"{test_name} {index}: \033[91mFAILED\033[0m, MEMORY: \033[92mPASSED\033[0m")
    else:
        print(f"{test_name} {index}: \033[91mFAILED\033[0m, MEMORY: \033[91mFAILED\033[0m")

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
        print_result("testLevelA", i, output_passed, memory_passed)

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
        print_result("testLevelAPlus", i, output_passed, memory_passed)

def run_levelB(exe_path):
    timeout = 15
    for i in range(1, 101):
        input_prefix = "input2/testLevelB"
        output_prefix = "output/TestLevelB"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput2/TestLevelB{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelB{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        print_result("testLevelB", i, output_passed, memory_passed)

def run_levelC(exe_path):
    timeout = 15
    for i in range(1, 51):
        input_prefix = "input3/testLevelC"
        output_prefix = "output/TestLevelC"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput3/TestLevelC{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelC{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        print_result("testLevelC", i, output_passed, memory_passed)

def run_levelD(exe_path):
    timeout = 30
    for i in range(1, 21):
        input_prefix = "input3/testLevelD"
        output_prefix = "output/TestLevelD"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput3/TestLevelD{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelD{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        print_result("testLevelD", i, output_passed, memory_passed)

def run_levelZ(exe_path):
    timeout = 150
    for i in range(1, 11):
        input_prefix = "input3/testLevelZ"
        output_prefix = "output/TestLevelZ"
        input_path = f"{input_prefix}{i}.in"
        output_path = f"{output_prefix}{i}.out"
        test_output_path = f"testOutput3/TestLevelZ{i}.out"
        valgrind_output_path = f"valgrindOutput/testLevelZ{i}.log"

        output_passed, memory_passed = run_test_with_valgrind(exe_path, input_path, output_path, test_output_path, valgrind_output_path, timeout)
        print_result("testLevelZ", i, output_passed, memory_passed)

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
        print_result("testBattleTreason", i, output_passed, memory_passed)

if __name__ == "__main__":
    exe_path = "./a.out"
    output_directory = "output"
    valgrind_output_directory = "valgrindOutput"

    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    if not os.path.exists(valgrind_output_directory):
        os.makedirs(valgrind_output_directory)

    print("***************************** Senior Abd El Haleem (Simple) *****************************")
    run_levelA(exe_path)
    print("***************************** Junior Abd El Haleem (Easy) *****************************")
    run_levelAPlus(exe_path)
    print("****************************  The Companion Bebo (Medium) ****************************")
    run_levelB(exe_path)
    print("***************************** Shadi BTMN (Hard) *****************************")
    run_levelC(exe_path)
    print("***************************** The one and only 2pifeeq (Impossible) *****************************")
    run_levelD(exe_path)
    print("**************************  The Elder Sliman (IDK at this point?) **************************")
    run_levelZ(exe_path)
    print("****************************  @mabusalieh Special, King of the Andals and the Rhoynar, and the First Men, Lord of the Seven Kingdoms, and Protector of the Realm. Rider of Khalisee of the great grass sea,the Unburnt, Queen of Meereen, Breaker of Chains and Mother of Dragons. (Special Edition)  *****************************")
    run_BattleTreason(exe_path)