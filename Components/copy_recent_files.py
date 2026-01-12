"""
Script to copy recently modified files from CAL_Source and IO_Source to ToUploadToWiki.

This script:
1. Scans CAL_Source and IO_Source directories recursively
2. Finds files modified in the last 2 months OR since the last script run
3. Copies those files to ToUploadToWiki folder in a flat format (no subdirectories)
"""

import os
import shutil
import json
from datetime import datetime, timedelta
from pathlib import Path

# Configuration - you can change these if needed
CAL_SOURCE_DIR = "CAL_Source"
IO_SOURCE_DIR = "IO_Source"
TARGET_DIR = "ToUploadToWiki"
STATE_FILE = "copy_script_state.json"  # File to remember last run time

# Number of months to look back (2 months)
MONTHS_TO_CHECK = 2


def load_last_run_time():
    """
    Load the timestamp of the last script run from a file.
    If the file doesn't exist, return None (meaning we'll check all files from 2 months ago).
    """
    if os.path.exists(STATE_FILE):
        try:
            with open(STATE_FILE, 'r') as f:
                data = json.load(f)
                # Convert the stored timestamp string back to a datetime object
                last_run_str = data.get('last_run_time')
                if last_run_str:
                    return datetime.fromisoformat(last_run_str)
        except Exception as e:
            print(f"Warning: Could not read state file: {e}")
            print("Will check files from the last 2 months.")
    return None


def save_last_run_time():
    """
    Save the current time to a file so we remember when we last ran the script.
    """
    try:
        current_time = datetime.now()
        data = {
            'last_run_time': current_time.isoformat()
        }
        with open(STATE_FILE, 'w') as f:
            json.dump(data, f, indent=2)
    except Exception as e:
        print(f"Warning: Could not save state file: {e}")


def should_copy_file(file_path, last_run_time):
    """
    Check if a file should be copied.
    Returns True if the file was modified:
    - In the last 2 months, OR
    - Since the last script run (if we have a last run time)
    """
    try:
        # Get when the file was last modified
        file_mod_time = datetime.fromtimestamp(os.path.getmtime(file_path))
        
        # Calculate the cutoff date (2 months ago)
        two_months_ago = datetime.now() - timedelta(days=MONTHS_TO_CHECK * 30)
        
        # Check if file was modified in the last 2 months
        if file_mod_time >= two_months_ago:
            return True
        
        # If we have a last run time, also check if file was modified since then
        if last_run_time is not None:
            if file_mod_time >= last_run_time:
                return True
        
        return False
    except Exception as e:
        print(f"Warning: Could not check file {file_path}: {e}")
        return False


def copy_file_to_target(source_path, target_dir):
    """
    Copy a file directly to the target directory (flat structure, no subdirectories).
    
    If a file with the same name already exists, it will be renamed with a number.
    
    For example:
    - CAL_Source/ADC.fcfx -> ToUploadToWiki/ADC.fcfx
    - IO_Source/displays/LCD.fcfx -> ToUploadToWiki/LCD.fcfx
    """
    try:
        # Get just the filename (without the path)
        file_name = os.path.basename(source_path)
        
        # Create the target path (directly in the target directory)
        target_path = os.path.join(target_dir, file_name)
        
        # If a file with this name already exists, add a number to make it unique
        if os.path.exists(target_path):
            # Split the filename into name and extension
            name, ext = os.path.splitext(file_name)
            counter = 1
            
            # Keep trying until we find a unique filename
            while os.path.exists(target_path):
                new_name = f"{name}_{counter}{ext}"
                target_path = os.path.join(target_dir, new_name)
                counter += 1
            
            print(f"  (Renamed to {os.path.basename(target_path)} to avoid conflict)")
        
        # Copy the file
        shutil.copy2(source_path, target_path)
        return True
    except Exception as e:
        print(f"Error copying {source_path}: {e}")
        return False


def scan_and_copy_directory(source_dir, target_dir, last_run_time):
    """
    Recursively scan a directory and copy recently modified files to the target directory.
    Files are copied directly to the target directory (flat structure, no subdirectories).
    """
    if not os.path.exists(source_dir):
        print(f"Warning: Source directory '{source_dir}' does not exist. Skipping.")
        return 0
    
    files_copied = 0
    
    # Walk through all files and subdirectories
    for root, dirs, files in os.walk(source_dir):
        for file_name in files:
            source_file_path = os.path.join(root, file_name)
            
            # Check if this file should be copied
            if should_copy_file(source_file_path, last_run_time):
                # Copy the file directly to the target directory (flat structure)
                if copy_file_to_target(source_file_path, target_dir):
                    files_copied += 1
                    print(f"Copied: {source_file_path}")
    
    return files_copied


def main():
    """
    Main function that runs the script.
    """
    print("=" * 60)
    print("File Copy Script - CAL_Source and IO_Source")
    print("=" * 60)
    print()
    
    # Load the last run time
    last_run_time = load_last_run_time()
    if last_run_time:
        print(f"Last script run: {last_run_time}")
    else:
        print("First time running script - checking files from last 2 months")
    print()
    
    # Make sure the target directory exists
    if not os.path.exists(TARGET_DIR):
        os.makedirs(TARGET_DIR)
        print(f"Created target directory: {TARGET_DIR}")
    
    total_files_copied = 0
    
    # Scan and copy from CAL_Source
    print(f"Scanning {CAL_SOURCE_DIR}...")
    files_copied = scan_and_copy_directory(CAL_SOURCE_DIR, TARGET_DIR, last_run_time)
    total_files_copied += files_copied
    print(f"Copied {files_copied} files from {CAL_SOURCE_DIR}")
    print()
    
    # Scan and copy from IO_Source
    print(f"Scanning {IO_SOURCE_DIR}...")
    files_copied = scan_and_copy_directory(IO_SOURCE_DIR, TARGET_DIR, last_run_time)
    total_files_copied += files_copied
    print(f"Copied {files_copied} files from {IO_SOURCE_DIR}")
    print()
    
    # Save the current run time for next time
    save_last_run_time()
    
    # Summary
    print("=" * 60)
    print(f"Total files copied: {total_files_copied}")
    print(f"Files copied to: {TARGET_DIR}")
    print("Script completed successfully!")
    print("=" * 60)


# Run the script when executed
if __name__ == "__main__":
    main()

