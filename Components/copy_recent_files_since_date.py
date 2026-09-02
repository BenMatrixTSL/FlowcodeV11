"""
Script to copy Flowcode files from CAL_Source and IO_Source to ToUploadToWiki
that have been modified since a fixed cutoff date.

Unlike copy_recent_files.py, this script:
- Always uses a fixed cutoff date (does not read/write copy_script_state.json)
- Copies every matching file modified since that date, regardless of whether
  it has already been discovered/uploaded before
- Only includes files with extensions: .fcfx, .fcsx, .fcweb
"""

import os
import shutil
from datetime import datetime

# Configuration
CAL_SOURCE_DIR = "CAL_Source"
IO_SOURCE_DIR = "IO_Source"
TARGET_DIR = "ToUploadToWiki"

# Fixed cutoff date - files modified on or after this date will be copied
CUTOFF_DATE = datetime(2026, 6, 26)

# Only copy these Flowcode-related file types
ALLOWED_EXTENSIONS = {".fcfx", ".fcsx", ".fcweb"}


def should_copy_file(file_path):
    """
    Check if a file should be copied: modified on or after CUTOFF_DATE.
    """
    try:
        file_mod_time = datetime.fromtimestamp(os.path.getmtime(file_path))
        return file_mod_time >= CUTOFF_DATE
    except Exception as e:
        print(f"Warning: Could not check file {file_path}: {e}")
        return False


def copy_file_to_target(source_path, target_dir):
    """
    Copy a file directly to the target directory (flat structure, no subdirectories).

    If a file with the same name already exists, it will be renamed with a number.
    """
    try:
        file_name = os.path.basename(source_path)
        target_path = os.path.join(target_dir, file_name)

        if os.path.exists(target_path):
            name, ext = os.path.splitext(file_name)
            counter = 1

            while os.path.exists(target_path):
                new_name = f"{name}_{counter}{ext}"
                target_path = os.path.join(target_dir, new_name)
                counter += 1

            print(f"  (Renamed to {os.path.basename(target_path)} to avoid conflict)")

        shutil.copy2(source_path, target_path)
        return True
    except Exception as e:
        print(f"Error copying {source_path}: {e}")
        return False


def scan_and_copy_directory(source_dir, target_dir):
    """
    Recursively scan a directory and copy files modified since CUTOFF_DATE
    to the target directory (flat structure, no subdirectories).
    """
    if not os.path.exists(source_dir):
        print(f"Warning: Source directory '{source_dir}' does not exist. Skipping.")
        return 0

    files_copied = 0

    for root, dirs, files in os.walk(source_dir):
        for file_name in files:
            _, ext = os.path.splitext(file_name)
            if ext.lower() not in ALLOWED_EXTENSIONS:
                continue

            source_file_path = os.path.join(root, file_name)

            if should_copy_file(source_file_path):
                if copy_file_to_target(source_file_path, target_dir):
                    files_copied += 1
                    print(f"Copied: {source_file_path}")

    return files_copied


def main():
    print("=" * 60)
    print("File Copy Script - Files modified since cutoff date")
    print("=" * 60)
    print()
    print(f"Cutoff date: {CUTOFF_DATE}")
    print("(This run ignores copy_script_state.json and re-copies all")
    print(" matching files modified on or after the cutoff date.)")
    print()

    if not os.path.exists(TARGET_DIR):
        os.makedirs(TARGET_DIR)
        print(f"Created target directory: {TARGET_DIR}")

    total_files_copied = 0

    print(f"Scanning {CAL_SOURCE_DIR}...")
    files_copied = scan_and_copy_directory(CAL_SOURCE_DIR, TARGET_DIR)
    total_files_copied += files_copied
    print(f"Copied {files_copied} files from {CAL_SOURCE_DIR}")
    print()

    print(f"Scanning {IO_SOURCE_DIR}...")
    files_copied = scan_and_copy_directory(IO_SOURCE_DIR, TARGET_DIR)
    total_files_copied += files_copied
    print(f"Copied {files_copied} files from {IO_SOURCE_DIR}")
    print()

    print("=" * 60)
    print(f"Total files copied: {total_files_copied}")
    print(f"Files copied to: {TARGET_DIR}")
    print("Script completed successfully!")
    print("=" * 60)


if __name__ == "__main__":
    main()
