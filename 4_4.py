import math
import multiprocessing
import time


NUM_PROCESSES = 8  

START_range = int(math.pow(10, 5))
END_range = int(math.pow(10, 6))

def find_numbers_in_range(start, end):

    process_name = multiprocessing.current_process().name
    print(f"Процесс {process_name} начал работу на диапазоне [{start}, {end-1}]")
    
    found = []
    for i in range(start, end):
        c = 0
        for j in range(2, int(i**0.5) + 1):
            if i % j == 0:
                if j * j == i:
                    c += 1
                else:
                    c += 2
            if c > 4:
                break
        if c == 3:
            found.append(i)
            
    print(f"Процесс {process_name} завершил работу, найдено: {len(found)} чисел")
    return found

if __name__ == "__main__":
    print(f"Поиск в диапазоне [{START_range}, {END_range-1}] с использованием {NUM_PROCESSES} процессов\n")

    start_time = time.time()
    tasks = []
    chunk_size = (END_range - START_range) // NUM_PROCESSES
    for i in range(NUM_PROCESSES):
        start = START_range + i * chunk_size
        end = start + chunk_size if i < NUM_PROCESSES - 1 else END_range
        tasks.append((start, end)) 

    with multiprocessing.Pool(processes=NUM_PROCESSES) as pool:
        results_from_processes = pool.starmap(find_numbers_in_range, tasks)

    ITOG = []
    for result_list in results_from_processes:
        ITOG.extend(result_list)
         
    end_time = time.time()
    
    print("\nВсе процессы завершились.")
    print("Поиск завершен!")
    print(f"Затраченное время - {end_time - start_time:.2f} секунд.")
     
    if ITOG:
        ITOG.sort()
        print(f"Найденные числа ({len(ITOG)} шт.):")
        print(ITOG)
    else:
        print("Найденные числа (0 шт.):")
        print("[]")
