# Temporizador de um disparo

## Etapas da execução

Os requisitos para a realização desta atividade são:

1. Caso o usuário clique no botão (pushbutton), os três LEDs serão ligados (todos em nível alto). A partir da primeira rotina de atraso, ocorrerá uma mudança de estado para dois LEDs ligados e, em seguida, apenas um. Obs.: veja o vídeo associado a esta prática no [link](https://www.dropbox.com/scl/fi/7faa7ib6bjrxncr2dxnf7/2025-01-26-14-01-54.mkv?rlkey=wqvef7zpxpuwvz2joj6qucasd&dl=0)
2. O temporizador do alarme deve ser ajustado para um atraso de 3 segundos (3.000ms), entre os estados de acionamento dos LEDs. 
3. A mudança de estado dos LEDs deve ser implementada em funções de call-back do temporizador, a exemplo da rotina trabalhada na aula síncrona - `turn_off_callback()`.
4. O botão só pode alterar o estado dos LEDs quando o último LED for desligado. Deste modo, durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função call-back.
5. Com o emprego da Ferramenta Educacional BitDogLab, faça um experimento com o código deste exercício utilizando o LED RGB – GPIOs 11, 12 e 13 e o Botão A, GPIO 05.
6. [x] Opcional: Implementar uma rotina em software para atenuação do efeito bouncing no botão (software debounce).