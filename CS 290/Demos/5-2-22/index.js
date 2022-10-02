window.addEventListener('click', function () {
    console.log("== The window was clicked")
})

function boxClickListener() {
    console.log("== A box was clicked")
}

function buttonClickListener(event) {
    console.log("== A button was clicked")
    console.log("   - Event:", event)
    console.log("   - event.target", event.target)
    //events get passed up and up so this will always be the events attach point
    console.log("   - event.currentTarget", event.currentTarget)

    var box = event.target.parentNode
    box.classList.toggle('highlighted')
}

var boxes = document.getElementsByClassName('box')
var buttons = document.getElementsByClassName('in-box-button')

for (var i = 0; i < boxes.length; i++) {
    boxes[i].addEventListener('click', boxClickListener)
}

for (var i = 0; i < buttons.length; i++) {
    buttons[i].addEventListener('click', buttonClickListener)
}