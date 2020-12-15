import firebase from "../firebase";

const db = firebase.database();

class UsersDataService {
  getAll() {
    return db.ref('users').once('value');
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