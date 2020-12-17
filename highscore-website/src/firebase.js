import firebase from "firebase";
// import "firebase/auth";
// import "firebase/firestore";
import "firebase/database";

const firebaseConfig = {
  apiKey: "AIzaSyDel7dxNATkHd_r8XZBQCoJ71t_SgexArM",
  authDomain: "welican-gemina-18f94.firebaseapp.com",
  databaseURL: "https://welican-gemina-18f94-default-rtdb.firebaseio.com",
  projectId: "welican-gemina-18f94",
  storageBucket: "welican-gemina-18f94.appspot.com",
  messagingSenderId: "531465433094",
  appId: "1:531465433094:web:99d88972dea0498fb29387",
  measurementId: "G-24XHV8TF7F"
};

firebase.initializeApp(firebaseConfig);

export default firebase;