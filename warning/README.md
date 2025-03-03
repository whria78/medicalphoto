# Warning

## Memory Requirements
To ensure optimal performance, at least **64GB of RAM** is recommended. If your system has less memory, you may experience slow processing times or application crashes.

## Microsoft Visual C++ Redistributable
This application requires an updated version of the **Microsoft Visual C++ Redistributable for Visual Studio 2015, 2017, 2019, and 2022**.

If you encounter an issue related to missing or outdated redistributable packages, please download the latest version from the official Microsoft website:

[Download Microsoft Visual C++ Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022)

## Model Download
The application requires GGUF model files to function correctly. If the `./gguf` directory does not contain any `.gguf` files, please download the required models from Hugging Face.

### Qwen2-VL 72B Model:
- Repository: [Qwen2-VL-72B-Instruct-GGUF](https://huggingface.co/second-state/Qwen2-VL-72B-Instruct-GGUF)
- Required files:
  - `Qwen2-VL-72B-Instruct-Q4_K_M.gguf`
  - `Qwen2-VL-72B-Instruct-vision-encoder.gguf`

### Qwen2-VL 7B Model:
- Repository: [Qwen2-VL-7B-Instruct-GGUF](https://huggingface.co/second-state/Qwen2-VL-7B-Instruct-GGUF)
- Required files:
  - `Qwen2-VL-7B-Instruct-Q4_K_M.gguf`
  - `Qwen2-VL-7B-Instruct-vision-encoder.gguf`

Download and place the appropriate files inside the `./gguf` directory.

## Unicode Support Issue
If you receive an error related to Unicode support, ensure that your system is using **UTF-8** encoding.

### How to Enable UTF-8 Support:

![RegionSetting](https://whria78.github.io/medicalphoto/imgs/RegionSetting.png)

1. Open **Settings** > **Time & Language** > **Language & region**.
2. Click **Administrative language settings**.
3. Under **Language for non-Unicode programs**, click **Change system locale**.
4. Check **Beta: Use Unicode UTF-8 for worldwide language support**.
5. Restart your computer.

If you continue to experience issues, please contact support or refer to the documentation.

