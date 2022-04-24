$(window).on("load", function () {
    $("#loading").fadeOut("slow");
});

function submitAvis() {
    let objet = document.getElementById("Objet").value;
    let demande = document.getElementById("Demande").value;
    window.open('mailto:kohfrais@outlook.com?subject=' + objet + '&body=' + demande);
}

function initMap() {
    const lannion = { lat: 48.7322183, lng: -3.4587994 };
    const map = new google.maps.Map(document.getElementById("map"), {
        zoom: 14,
        center: lannion,
    });
    new google.maps.Marker({
        position: lannion,
        map: map,
    });
    new google.maps.Marker({
        position: { lat: 48.7336726, lng: -3.4374372 },
        map: map,
    });
    new google.maps.Marker({
        position: { lat: 48.7309716, lng: -3.4607875 },
        map: map,
    });
}