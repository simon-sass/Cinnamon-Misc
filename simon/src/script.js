startButton = document.getElementById('start-reset');
button1 = document.getElementById('button-one');
button2 = document.getElementById('button-two');
button3 = document.getElementById('button-three');
button4 = document.getElementById('button-four');
buttons = [button1, button2, button3, button4]

const timer = ms => new Promise(res => setTimeout(res, ms))
let correctSequence = [];
let currentSequence = [];

function start() {
    for (let i = 0; i < 4; i++) {
        buttons[i].addEventListener('click', flashFunction(buttons[i]));
        buttons[i].addEventListener('click', addChoiceFunction(i + 1));
    }
    startButton.innerHTML = "Reset";
    readNextSequence();
    startButton.addEventListener('click', reset);
    startButton.removeEventListener('click', start);
}

function flashFunction(button) {
    return function(){
        button.style.backgroundColor = 'white';
        setTimeout(() => { button.style.backgroundColor = ''; 
    }, 300);};
}

function flash(button) {
    button.style.backgroundColor = 'white';
    setTimeout(() => { button.style.backgroundColor = ''; }, 300);
}

function gameLost() {
    correctSequence = [];
    currentSequence = [];
    for (let i = 0; i < 4; i++) {
        buttons[i].removeEventListener('click', flashFunction(buttons[i]));
        buttons[i].removeEventListener('click', addChoiceFunction(i + 1));
    }
    startButton.innerHTML = "Try again";
}

async function reset() {
    correctSequence = [];
    currentSequence = [];
    for (let i = 0; i < 4; i++) {
        buttons[i].removeEventListener('click', flashFunction(buttons[i]));
        buttons[i].removeEventListener('click', addChoiceFunction(i + 1));
    }
    startButton.innerHTML = "Reset";
    await timer(500);
    readNextSequence();
}

async function resetCurrent() {
    currentSequence = [];
    await timer(500);
    readNextSequence();
}

function addChoiceFunction(choice) {
    return function () {
        if (currentSequence.length - 1 > correctSequence.length) {return;}
        if (correctSequence[currentSequence.length] == choice) {
            currentSequence += choice;
        } else {
            gameLost();
            return;
        }
        if (correctSequence.length == currentSequence.length) {
            resetCurrent();
        }
    }
}

function addChoice(choice) {
    if (currentSequence.length - 1 > correctSequence.length) {return;}
    if (correctSequence[currentSequence.length] === choice) {
        currentSequence += choice;
    } else {
        gameLost();
        return;
    }
    readNextSequence();
}

async function readNextSequence() {
    correctSequence += (Math.floor(Math.random() * 4) + 1)
    for (let i = 0; i < correctSequence.length; i++) {
        flash(buttons[correctSequence[i]-1]);
        await timer(500);
    }
}

startButton.addEventListener('click', start);