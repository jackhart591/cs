var photoCardContainer = document.getElementById("photo-card-container")

//Example of how they can hack using innerHTML
var userSuppliedValue = "<img src=x onerror=\"alert('Hacked')\" />"
// photoCardContainer.innerHTML += '<section class="photo-card">' + userSuppliedValue + "</section>"

/* Example of a photo card
    <section class="photo-card">
        <div class="img-container">
            <img class="person-photo-img" src="https://vignette3.wikia.nocookie.net/starwars/images/6/62/LukeGreenSaber-MOROTJ.png" />
        </div>
        <div class="caption">
            Luke ready to fight.
        </div>
    </section>
*/
function createPhotoCard(photoURL, caption) {
    //cannot use innerHTML if there's user input because they can input HTML
    //to destroy the site (see above)

    var photoCardSection = document.createElement('section')
    photoCardSection.classList.add('photo-card')
    photoCardSection.classList.add('another-class')
    photoCardSection.classList.remove('another-class')

    var imgContainerDiv = document.createElement('div')
    imgContainerDiv.classList.add('img-container')
    photoCardSection.appendChild(imgContainerDiv)

    var img = document.createElement('img')
    img.classList.add('person-photo-img')
    img.src = photoURL
    imgContainerDiv.appendChild(img)

    var captionDiv = document.createElement('caption')
    captionDiv.classList.add('caption')
    captionDiv.textContent = caption
    photoCardSection.appendChild(captionDiv)

    //currently everything is just in memory, not in DOM

    photoCardContainer.appendChild(photoCardSection)

    //now in div

}

createPhotoCard("http://placekitten.com/480/480?image=1", "Luke as a kitty")
createPhotoCard("http://placekitten.com/480/480?image=4394", userSuppliedValue)