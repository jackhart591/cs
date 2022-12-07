const filterDD = document.getElementById('project-dropdown')
const filterButton = document.getElementById('filter-button')
const clearFilterButton = document.getElementById('clear-filter-button')
const searchBar = document.getElementById('query')
const searchButton = document.getElementById('search-button')

filterButton.addEventListener('click', function(e) {
    window.location = `/filter=${filterDD.value}`
    addText(`Project {}`)
})

clearFilterButton.addEventListener('click', function(e) {
    window.location = '/'
})

searchButton.addEventListener('click', function(e) {
    window.location = `/name=${searchBar.value}`
})

export default { addText }