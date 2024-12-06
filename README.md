# ASCII Art Generator

Turn your images, videos, and GIFs into live ASCII art directly in your terminal!  
This tool converts any provided input media into ASCII or braille characters, optionally with color, and plays them right inside your terminal window. Perfect for adding a unique, retro touch to your favorite media.

## Features

- **Image to ASCII**: Convert `.jpg`, `.png`, `.jpeg`, `.bmp`, `.webp`, `.tif(f)` files into ASCII art.
- **Video to ASCII**: Convert `.mp4`, `.avi`, `.mov`, `.mkv`, `.flv` files into ASCII video, rendered frame by frame.
- **GIF Support**: Animate ASCII art with `.gif` files.
- **Color & Braille Modes**: Toggle full-color ASCII or high-resolution braille characters.
- **Aspect Ratio Control**: Adjust character aspect ratio for more accurate shapes.
- **Terminal-Friendly**: Just run in your terminal. No GUI needed!

## Dependencies

You’ll need the following installed:

- **C++17 compatible compiler** (e.g., `g++`)
- **OpenCV 4** or newer (for handling image & video frames)
- **ImageMagick** with Magick++ (for handling GIF frames)
- **ncurses** (for terminal control and stable video output)

### Installing Dependencies (MacOS/Homebrew)

```bash
brew install opencv imagemagick ncurses
```

### Installing Dependencies (Debian/Ubuntu)

```bash
sudo apt-get update
sudo apt-get install libopencv-dev libmagick++-dev libncurses5-dev g++
```

*Adjust based on your platform’s package manager.*

## Building the Project

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/ascii_art_generator.git
   cd ascii_art_generator
   ```

2. Build the project using the provided Makefile:
   ```bash
   make
   ```

   This will create an executable named `ascii_art_generator` in the project directory.

## Running the Tool

The basic usage:
```bash
./ascii_art_generator <input_file> [options]
```

**Examples:**
- Convert an image:
  ```bash
  ./ascii_art_generator my_image.jpg
  ```
- Convert a video with color output and a specified width:
  ```bash
  ./ascii_art_generator my_video.mp4 -C -W 100
  ```
- Render a GIF in braille mode with custom aspect ratio:
  ```bash
  ./ascii_art_generator my_animation.gif -B -A 0.45
  ```

## Command-Line Options

- `--color` or `-C`: Enable color ASCII output.
- `--width <num>` or `-W <num>`: Set output width (in characters). Defaults to terminal width if not specified.
- `--braille` or `-B`: Use braille characters instead of ASCII for higher resolution.
- `--char-aspect <val>` or `-A <val>`: Set the character aspect ratio (float) to better match the original media’s proportions.

**Pro Tip:** Adjusting the `--char-aspect` (`-A`) value can significantly improve how your ASCII art looks. Experiment with values like `0.4` to `0.6` until you find a good fit.

## Tips & Tricks

- **Resize Your Terminal:** Larger terminals allow for more detail.
- **Experiment With Different Fonts:** Monospaced fonts vary in character aspect ratio. Trying a different font or changing your terminal size might improve results.
- **Use Color Sparingly:** While color can look cool, grayscale ASCII sometimes offers better definition.

## Known Issues & Limitations

- Videos with very high resolution might be slow or not very readable at a small terminal size.
- Aspect ratios might need tweaking depending on the terminal font. There's no universal perfect value—just experiment!

## Contributing

Contributions are welcome! If you have suggestions, find bugs, or want to add new features:

1. Fork the repo.
2. Create a new branch: `git checkout -b my-feature`
3. Make changes and test thoroughly.
4. Submit a pull request.

## License

This project is open-sourced under the [MIT license](LICENSE).

---

Enjoy turning your media into nostalgic ASCII vibes! Feel free to open issues if you run into any problems.
