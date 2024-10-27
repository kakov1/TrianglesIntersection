def compare_files(file1_path, file2_path):
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        line_num = 1
        differences_found = False

        for line1, line2 in zip(file1, file2):
            if line1 != line2:
                print(f"Различие в строке {line_num}:")
                print(f"Файл 1: {line1.strip()}")
                print(f"Файл 2: {line2.strip()}")
                print()
                differences_found = True
            line_num += 1

        # Проверка, если один файл длиннее другого
        for line in file1:
            print(f"Файл 1 имеет дополнительную строку {line_num}: {line.strip()}")
            line_num += 1
            differences_found = True

        for line in file2:
            print(f"Файл 2 имеет дополнительную строку {line_num}: {line.strip()}")
            line_num += 1
            differences_found = True

        if not differences_found:
            print("Файлы идентичны.")

# Пример использования
compare_files('../build/tests/ans.txt', './tests/answer16.txt')