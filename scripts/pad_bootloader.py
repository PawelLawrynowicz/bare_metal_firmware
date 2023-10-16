from pathlib import Path

def pad_bootloader():
  project_dir = Path(__file__).parent.parent

  BOOTLOADER_SIZE = 0x8000
  BOOTLOADER_FILE = project_dir / "build" / "bootloader.bin"

  with open(BOOTLOADER_FILE, "rb") as f:
    raw_file = f.read()

  bytes_to_pad = BOOTLOADER_SIZE - len(raw_file)
  padding = bytes([0xff for _ in range(bytes_to_pad)])

  with open(BOOTLOADER_FILE, "wb") as f:
    f.write(raw_file + padding)

  print(f"Size of .bin file before padding: {len(raw_file)}")
  print(f"Size of .bin file after padding: {len(raw_file + padding)}")

  return 0

pad_bootloader()
