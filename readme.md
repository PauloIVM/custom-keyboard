# My Custom Keyboard ⌨️

### Sumário:
- [1 - Introdução](#1---introdução)
- [2 - Motivação e Construção do Projeto](#2---motivação-e-construção-do-projeto)
- [3 - Hardware](#3---hardware)
- [4 - Software](#4---software)

## 1 - Introdução

Este é um projeto de software e hardware, onde transformei um Redragon Mitra K551 em um teclado split totalmente customizável, com layers e incluindo um componente especial: um mouse de _joystics_.

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/e9e20eb4-6c2c-4bad-bd4b-35b1f91c0921)

## 2 - Motivação e Construção do Projeto

Há alguns meses, meu interesse em aprimorar minhas habilidades de digitação e utilização de atalhos cresceu significativamente. No entanto, a dependência do mouse era (e ainda é, em certa medida) uma barreira considerável. Inicialmente, desenvolvi apenas o mouse analógico, visando manter minhas mãos sempre próximas do teclado; e incentivando a utilização de atalhos em detrimento do mouse convencional.

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/aee006d4-4c1e-4a40-a4d0-c1c7c63bddaf)

Entretanto, esse dispositivo não proporcionou o efeito desejado. Sua dimensão dificultava na digitação. Por alguns meses deixei o projeto de lado; contudo, ao final, percebi que esse mouse se integraria de maneira mais adequada a um teclado split.

Assim, comecei a pesquisar mais sobre essa categoria de teclados. O que me surpreendeu foram os preços (na casa dos 1000 reais). Diante disso, pensei: "O que me impede de jogar fora a eletrônica desse Redragon e reconstruir um teclado split a partir da carcaça dele? De custos eu teria os arduinos, diodos e fios, algo na casa dos 200 reais, e o resto dos materiais eu tiraria do próprio teclado".

Dessa forma, dei continuidade ao projeto. Como evidenciado nas imagens a seguir, procedi com a remoção da placa do meu teclado, dividi a carcaça em dois e, por fim, realizei a soldagem manual dos switches em um Arduino.

![5](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/0fd848ed-57b7-4765-a498-79e50013f8d8)

![9](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/9fd293bc-f831-409d-8edb-e9a7e9b35a38)

![12](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/8dfde9fe-4ff4-49ca-bdb3-31ee560ed2f3)

![20](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/c3cea75e-0690-45f5-bbdb-cb2691cca659)

## 3 - Hardware

A seguir, apresento a relação de materiais utilizados na montagem do hardware:

Ferramentas para confecção e prototipagem:
- Estação de solda;
- Micro-retífica;
- Cola quente;
- Cola super bonder;

Peças adquiridas:
- 100 diodos 1n4148;
- Rolo de fio wire wrap 30awg;
- 3 arduinos Pro Micro - Atmega32u4;

Peças reutilizadas:
- Base metálica do Redragon Mitra K551;
- Keycaps do Redragon Mitra K551;
- Switches blues do Redragon Mitra K551;
- Joystics (removidos de uma manete de PS2 antiga);
- Estrutura de plástico do Redragon Mitra K551;

Caso esteja montando um projeto similar, recomendo fortemente a utilização do Atmega32u4 por conta de sua funcionalidade nativa de ser reconhecido como um dispositivo USB HID. Caso escolha um microcontrolador sem esta funcionalidade, será preciso escrever seus próprios descritores e isso pode dificultar bastante o projeto.

### 3.1 - Mouse


Como mencionado anteriormente, esse componente atua como um mouse. O analógico esquerdo é destinado a realizar scrolls tanto na direção horizontal quanto vertical, enquanto o analógico direito controla o movimento do cursor. Dos três botões, um corresponde ao clique esquerdo do mouse, outro ao clique direito, e o terceiro tem a função de ajustar a sensibilidade, assemelhando-se ao ajuste de DPI em mouses convencionais.

Para uma compreensão visual detalhada, cada componente de hardware possui um PDF contendo o circuito esquemático. O circuito esquemático específico do mouse pode ser encontrado [aqui](https://github.com/PauloIVM/my-custom-keyboard/blob/master/components/mouse/schematic.pdf) ou na imagem a seguir.

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/32c7e92b-7c6c-4cf5-81fb-abe280bd29d5)

A construção do componente foi à base de muitas gambiarras. Fiz um pequeno suporte de madeira para comportar os botões e os joystics. Soldei os fios no arduino e colei tudo com cola quente e cola super bonder + bicarbonato. Além disso, com o plástico de outras partes do teclado que seriam descartadas, criei um "case" para comportar todo o componente e esconder os fios.

Um ponto importante é que me ajudou muito ter uma microretífica.

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/ba36725c-196f-4b5b-ae77-f2a70d3f7711)

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/8ea4626b-1666-4587-9f3c-a52034dbadba)

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/0f9629cb-4dca-4c3a-8606-24b883370142)

### 3.2 - Teclado

Para a construção tanto do lado esquerdo quanto do lado direito do teclado, montei um circuito matricial de diodos para cada um. A escolha de utilizar uma matriz visa otimizar o uso de pinos, uma vez que, se cada tecla fosse tratada como um input independente, seria necessário mais pinos do que o Arduino dispõe.

A inclusão dos diodos é necessária para prevenir um problema comum em teclados matriciais, conhecido como _ghosting_. Esse fenômeno ocorre quando múltiplas teclas são pressionadas de forma triangular, resultando na interpretação de uma tecla não pressionada como se estivesse sendo pressionada.

Para elucidar o funcionamento do circuito matricial de diodos, considere a simplificação abaixo:

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/32c253bc-aadf-4dfe-8333-4b0b2693ed7d)


Observe que, na linha R1, o botão mais à direita está pressionado (fechado). As linhas são configuradas como inputs PULL_UP, enquanto as colunas são definidas como outputs (todas com nível lógico LOW neste momento). Quando um botão é pressionado, a linha correspondente apresenta nível lógico LOW; caso nenhum botão esteja pressionado, a linha permanece com nível lógico HIGH.

Dessa maneira, em uma primeira etapa, realizamos uma varredura em busca de alguma linha com estado lógico LOW. Ao encontrar, interrompemos essa varredura e iniciamos uma inspeção nessa linha para identificar quais colunas estão sendo pressionadas.

Supondo que encontramos uma linha com nível lógico LOW, seguimos com uma varredura nas colunas para verificar quais alteram o estado da linha. Inicialmente, configuramos todas as colunas para HIGH, como ilustrado na imagem a seguir. Isso garante que, independentemente do botão estar aberto ou fechado, o valor da linha permanece em HIGH.

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/dbd4582f-3a57-474d-a48c-b180a10238ba)

Agora iteramos coluna por coluna, definindo cada uma delas como LOW sequencialmente. As colunas que, ao serem definidas como LOW, provocam a mudança do estado da linha para LOW são identificadas como aquelas que estão sendo pressionadas.

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/a9aa27f3-0733-4571-9610-cbce00f3d56e)

A construção de ambos os lados do teclado seguiu seus respectivos esquemáticos (seguem logo abaixo). A prototipação foi feita soldando-se os fios manualmente, conforme uma imagem já anexada em [2 - Motivação e Construção do Projeto](#2---motivação-e-construção-do-projeto).

#### 3.2.1 - Teclado Esquerdo

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/c116f7cd-754f-46b1-9c5a-7c60562bea03)

#### 3.2.2 - Teclado Direito

![image](https://github.com/PauloIVM/my-custom-keyboard/assets/59659732/4b28bf3e-3866-454b-8ad3-f744b0947da3)

## 4 - Software

Um primeiro cuidado importante a se ter é com relação à gravação dos arduinos. Devido à funcionalidade nativa de ser reconhecido como um USB HID, gravar um código defeituoso pode resultar no não reconhecimento do dispositivo pela IDE do Arduino. Se isso ocorrer, não entre em desespero, há uma solução; o Arduino, ao ser plugado, aguarda aproximadamente 8 segundos antes de executar o código fonte; assim, você consegue gravar um novo código nesse curto intervalo.

Neste tipo de projeto é bem comum se utilizar o https://qmk.fm/ para gerar o código fonte dos arduinos. É um caminho possível, mas eu preferi escrever todo o meu código, especialmente porque no meu projeto existem algumas peculiaridades que acredito que o qmk não contemple, como os joystics por exemplo.

Dentro da pasta _components_, encontramos três subpastas; cada uma com um arquivo _.ino_ referente a um dos três componentes de hardware.

O _.ino_ em `/components/mouse` pode ser compilado em um Arduino Pro Micro sem problemas, sendo necessário apenas ajustar os pinos conforme o seu projeto.

Os arquivos _.ino_ em `/components/keyboard-left` e `/components/keyboard-right` precisam de uma lib para funcionar, denominada _KeyboardHandler_ e disponível em `/lib/keyboardHandler`. Como esse trecho do código é comum aos dois lados do teclado, optei por organizá-lo no formato de uma biblioteca que precisa ser importada.

O _KeyboardHandler_ pode ser importado de diversas formas. Você pode copiar o código e colar em cada uma das pastas `/components/keyboard-left` e `/components/keyboard-right`; ou ainda gerar um _.zip_ e adicionar a lib pela IDE do arduino; ou, caso esteja usando uma distribuição linux, pode executar um `make build` na raiz do projeto e a biblioteca será automaticamente adicionada à IDE do Arduino.

Adicionado o _KeyboardHandler_, você precisará passar os pinos corretos do seu hardware e passar as camadas com os layouts de teclas que quiser. Perceba que normalmente os teclados não possuem todas as linhas com a mesma quantidade de colunas; mas isso não é um problema, serão apenas teclas na sua matriz que nunca serão clicadas.

Você poderá passar quantas camadas desejar, bastando ajustar a dimensão em `layersLength`. O número de linhas e colunas também pode ser personalizado. Por fim, para trocar de camada, basta escolher um botão na matriz e passar a key `KEY_LAYER_UP` ou `KEY_LAYER_DOWN`, assim esses botões serão responsáveis por trocar de layer (semelhante a um botão "fn").

Na branch master você encontrará as layers que eu tenho utilizado no momento, isto poderá ajudar a tirar quaisquer dúvidas.
