import os
import time

def get_process_info(pid):
    try:
        with open(f"/proc/{pid}/status", "r") as f:
            return f.read()
    except FileNotFoundError:
        return None

def main():
    while True:
        pids = [pid for pid in os.listdir("/proc") if pid.isdigit()]
        
        for pid in pids:
            process_info = get_process_info(pid)
            if process_info:
                print(f"Process ID: {pid}\n{process_info}\n{'='*40}")

        time.sleep(5)  # Adjust the sleep interval as needed

if __name__ == "__main__":
    main()

