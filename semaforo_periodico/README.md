# Semáforo Periódico

Este projeto implementa um semáforo periódico utilizando a Raspberry Pi Pico. O semáforo alterna entre os estados vermelho, amarelo e verde a cada 3 segundos, e imprime o estado atual no console a cada segundo.

## Requisitos

- Raspberry Pi Pico
- SDK do Pico configurado
- LEDs e resistores
- Fios de conexão

## Configuração de Hardware

Conecte os LEDs aos pinos GPIO da Raspberry Pi Pico conforme a tabela abaixo:

| LED          | Pino GPIO |
|--------------|-----------|
| LED Vermelho | GP11      |
| LED Amarelo  | GP12      |
| LED Verde    | GP13      |

## Compilação e Execução

1. Clone o repositório e navegue até o diretório do projeto:

    ```sh
    git clone <URL_DO_REPOSITORIO>
    cd <NOME_DO_DIRETORIO>
    ```

2. Configure o ambiente, compile e carregue o código no Raspberry Pi Pico utilizando o ambiente de desenvolvimento de sua preferência.

## Funcionamento

O programa inicializa os pinos GPIO dos LEDs como saída e configura um temporizador periódico que alterna o estado do semáforo a cada 3 segundos. O estado atual do semáforo é impresso no console a cada segundo.

### Estados do Semáforo

- **0: Vermelho** - LED vermelho aceso, LEDs amarelo e verde apagados.
- **1: Amarelo** - LED amarelo aceso, LEDs vermelho e verde apagados.
- **2: Verde** - LED verde aceso, LEDs vermelho e amarelo apagados.

## Código Fonte

O código fonte principal está localizado no arquivo *semaforo_periodico.c*