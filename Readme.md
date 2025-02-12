# Manipulação de ServoMotor através de PWM

Este projeto implementa a funcionalidade de controle de um ServoMotor e de um LED por meio de PWM no **Raspberry Pi Pico W**. A solucação foi desenvolvida de 2 formas, sendo uma por temporização recursiva e a outra por meio da função sleep_ms. O código é desenvolvido em **C** para sistemas embarcados e foi implementado na placa voltada a aprendizagem BitDogLab.

## Estrutura do Projeto

- **servomotor_add_repeting**: Pasta que contém o projeto implementado com o uso de temporização recursiva.
- **servomotor_sleep_ms**: Pasta que contém o projeto implementado com o uso da função sleep_ms.
- **CMakeLists.txt**: Definição dos processos de compilação e requisitos necessários.
- **pico_sdk_import.cmake**: Arquivo com as configurações de importação do Pico SDK.
- **servomotor.c**: Arquivo principal com o código que será compilado e inserido na placa.
- **diagram.json**: Arquivo contendo as configurações que estruturam a simulação da extensão Wokwi.

## Funcionalidades

- **Manipulação de Servomotor**: Faz com que o servomotor se movimente de modo controlado por meio de mudanças no PWM.  
- **Alterar intensidade do LED**: Altera o nível do brilho do LED baseado em mudanças no PWM.

## Requisitos

- **Hardware**:
  - Computador pessoal.
  - Raspberry Pi Pico W (RP2040).
  - 1 Servomotor.
  - 1 Led RGB.
  - Resistores.
  - Cabos indutores.
  - Cabo micro-USB para USB-A.

- **Software**:
  - Visual Studio Code
  - Pico SDK
  - Compilador ARM GCC
  - Extensão Wokwi para VSCode


## Vídeo demonstrativo 
[Assista aqui](https://drive.google.com/file/d/1FfB-oZv6XbIDkKohn70FPz4Sf00vushw/view?usp=sharing)
