// globals
let tossCount = 0;
let stepCount = 0;
// globals end here

const createArray = (length) => {
  const newArray = new Array(length);
  for (let i = 0; i < length; i++) newArray[i] = i + 1;
  return newArray;
};

const splitTheArray = (inputArr) => {
  subArrLen = inputArr.length / 2;
  const subArr1 = inputArr.slice(0, subArrLen);
  const subArr2 = inputArr.slice(subArrLen, inputArr.length);
  return { subArr1, subArr2 };
};

const removeTails = (inputArr) => {
  const newArray = inputArr.filter((i) => i != 0);
  return newArray;
};

const toss = () => {
  tossCount++;
  return Math.floor(Math.random() * 2) == 1 ? "Heads" : "Tails";
};

const divideAndToss = (inputArr) => {
  const { subArr1, subArr2 } = splitTheArray(inputArr);
  let wonPeople = [];
  for (let i = 0; i < subArr1.length; i++) {
    let tossResult = toss();
    tossResult == "Heads"
      ? wonPeople.push(subArr1[i])
      : wonPeople.push(subArr2[i]);
  }
  return wonPeople;
};

(function main() {
  const numberOfPeople = 1000;
  let peopleArray = createArray(numberOfPeople);

  // The step loop
  while (peopleArray.length > 1) {
    stepCount++;
    if (peopleArray.length % 2 != 0) {
      lastEl = peopleArray[peopleArray.length - 1];
      peopleArray.pop();
      peopleArray = divideAndToss(peopleArray);
      toss() == "Heads" ? peopleArray.push(lastEl) : "";
    } else {
      peopleArray = divideAndToss(peopleArray);
    }
  }

  const winner = {
    "The Winner": peopleArray[0],
    "Total Heads": stepCount,
    "Total Toss": tossCount,
  };

  console.table(winner);
})();
