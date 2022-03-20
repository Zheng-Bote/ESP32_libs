<div id="top"></div>
<br />
<div align="center">
<h3 align="center">ESP32 libraries</h3>

  <p align="center">
      (Arduino) libraries for ESP32 
      <br/>
      <br/>
    <a href="https://github.com/Zheng-Bote/ESP32_libs/wiki"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Zheng-Bote/ESP32_libs/issues">Report Bug</a>
    ·
    <a href="https://github.com/Zheng-Bote/ESP32_libs/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
### ESP32 libraries
(Arduino) libraries for ESP32 wihich maybe are usefull
* WiFi
* WiFi http client
* MQTT client (publish/subscribe)
* ESP32 system calls (eg. ESP32 deep sleep with intervall, get MAC address, ...)
* Lora
* SIM800 (eg. send/receive SMS) 
* ...


<!-- GETTING STARTED -->
## Getting Started

install the Arduino IDE or use the web online version

**Note that master is generally a work in progress, and you probably want to use a tagged release version.**

### Prerequisites

* PC or Laptop with Windows, MacOS or Linux *_^
* ESP32 connected
* install the Arduino IDE
  `https://www.arduino.cc/en/software`
* or use Arduino IDE online
  `https://create.arduino.cc/editor`
* some libraries needs additional Arduino libraries (e.g. PubSubClient. See header comments)

<p align="right">(<a href="#top">back to top</a>)</p>

### Installation

1. Clone the repo

   **Note that master is generally a work in progress, and you probably want to use a tagged release version.**
   ```sh
   git clone https://github.com/Zheng-Bote/ESP32_libs.git
   ```
2. copy the libs manually to /usr/local/include/ESP32/
   (CMake / Makefile coming soon...)
   ```sh
   sudo mkdir -d /usr/local/include/ESP32 && cp ./* /usr/local/include/ESP32/.
   ```
3. add required lib to your project
   `#include "ESP32/the_lib.h"`

4. load firmware on ESP32

<p align="right">(<a href="#top">back to top</a>)</p>


### Usage

 see <a href="https://github.com/Zheng-Bote/ESP32_libs/wiki" alt="Wiki" title="https://github.com/Zheng-Bote/ESP32_libs/wiki">Wiki</a> for details of the libraries

<p align="right">(<a href="#top">back to top</a>)</p>

 
<!-- ROADMAP -->
## Roadmap

- [x] list all libs with short description (see Wiki)
- [x] optimize header files with docu (mostly done, except older libs)
- [x] optimize mem usage (stack/heap)
- [ ] create CMake/Makefile for installation/updates
- [ ] ???

Maybe a Kanban board will be established (soon)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

ZHENG Robert Zhèng Bó Tè 郑 伯特

Project Link: [https://github.com/Zheng-Bote/ESP32_libs](https://github.com/Zheng-Bote/ESP32_libs)

<p align="right">(<a href="#top">back to top</a>)</p>

