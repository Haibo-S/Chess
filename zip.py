import os
import zipfile

def zip_files(directory, zip_name):
    # Create a ZipFile object
    with zipfile.ZipFile(zip_name, 'w', zipfile.ZIP_DEFLATED) as zipf:
        # Walk the directory tree
        for root, _, files in os.walk(directory):
            for file in files:
                # Check for Makefile, .h, .cc, and .pdf files
                if file == 'makefile' or file == 'Makefile' or file.endswith('.h') or file.endswith('.cc') or file.endswith('.pdf'):
                    # Create the complete filepath of the file in the directory
                    file_path = os.path.join(root, file)
                    # Add file to the zip file
                    zipf.write(file_path, os.path.relpath(file_path, directory))

# Usage
directory_to_zip = os.getcwd()  # Use the current working directory
zip_name = 'project.zip'
zip_files(directory_to_zip, zip_name)
