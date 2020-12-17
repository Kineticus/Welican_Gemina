import firebase from "../firebase";

const db = firebase.database();
const usersRef = db.ref('users');
const hsRef = db.ref('highscores');

class UsersDataService {
  getAll() {
    return usersRef.once('value');
  }

  getHighscores() {
    return hsRef.once('value');
  }

  getSpecificHighscores(game) {
    return hsRef.child(game).once('value');
  }

  create(user) {
    return db.add(user);
  }

  update(id, value) {
    return db.doc(id).update(value);
  }

  delete(id) {
    return db.doc(id).delete();
  }
}

export default new UsersDataService();