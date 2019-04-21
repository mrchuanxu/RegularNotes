var str = '123';
function change(str) {
  str = '456';
}
change(str);
console.log(str);//"123"
